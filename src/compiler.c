bool has_flag(Compiler_Options options, int flag)
{
    return options & flag;
}

bool is_source_file(String* string)
{
    return string_ends_with_cstr(string, FILE_EXTENSION);
}

static void print_help()
{
    printf("Usage: ske [options] file...\n\n");
    printf("Options\n");

    printf("  --h or -help            Display this information\n");
    printf("  -outfile <file>         Place the output into <file>\n");
    printf("  -assembly               Output assembly.\n");
    printf("  -compile                Compile and assemble, but do not link\n");
    printf("  -tokenizer              Tokenize and output tokens\n");
    printf("  -parser                 Parse and output AST\n");
    printf("  -ir                     Generate IR and output\n");
}

Compiler_Arguments parse_args(int argc, char** argv, Allocator* allocator)
{
    Compiler_Arguments arguments;
    arguments.options = OPT_NONE;
    arguments.input_file = NULL;
    arguments.out_path = NULL;

    for (i32 i = 1; i < argc; i++)
    {
        char* arg = argv[i];
        String string = string_create(arg);

        if (string.length >= 2)
        {
            if (string_equal_cstr(&string, "--t") || string_equal_cstr(&string, "-test"))
            {
                printf("Running tests...\n");

                /* String* command = string_create_from_arena("", 1 , ALLOCATOR(&string_arena)); */
            }
            else if (string_equal_cstr(&string, "-outfile"))
            {
                if(argc < i + 1)
                {
                    printf("No output file path provided for '%s' argument. Please provide a valid argument\n", string.str);
                    break;
                }
                arguments.out_path = string_allocate(argv[i + 1], allocator);
                i++;
            }
            else if (string_equal_cstr(&string, "-assembly"))
            {
                arguments.options |= OPT_ASSEMBLY_OUTPUT;
            }
            else if (string_equal_cstr(&string, "-tokenize"))
            {
                arguments.options |= OPT_TOK_OUTPUT;
            }
            else if (string_equal_cstr(&string, "-ir"))
            {
                arguments.options |= OPT_IR_OUTPUT;
            }
            else if (string_equal_cstr(&string, "-parser"))
            {
                arguments.options |= OPT_AST_OUTPUT;
            }
            else if (string_equal_cstr(&string, "--h") || string_equal_cstr(&string, "-help"))
            {
                print_help();
            }
            else if (is_source_file(&string))
            {
                arguments.input_file = string_copy(&string, allocator);
                char buf[128];
                String full_path = { .length = 128, .str = buf};
                if (!absolute_path(&string, &full_path))
                {
                    fprintf(stderr, "\x1b[1;37mInvalid input path: \x1b[0m%s\n", string.str);
                }
                else
                {
                    arguments.absolute_path = string_copy(&full_path, allocator);
                }
            }
            else
            {
                printf("Unknown argument '%s'. Try --h or -help to see available options.\n", arg);
                print_help();
                break;
            }
        }
    }

    return arguments;
}

bool Compiler_assemble_x86_with_input_file(String* file_path, String* output_path, Allocator* allocator)
{
    char *cmd[] = {"as", "-g", "-c", file_path->str, "-o", output_path->str, NULL};
    return run_subprocess(cmd);
}

bool Compiler_link(String* input_file_path, String* output_file_path, Allocator* allocator)
{
    char *cmd[] = {"ld", "-o", output_file_path->str, "-dynamic-linker", "/lib64/ld-linux-x86-64.so.2", "-lc", input_file_path->str, "-lm", "-no-pie", NULL};
    return run_subprocess(cmd); 
}

bool Compiler_compile(String* source, Compiler_Arguments arguments, Allocator* allocator)
{
    if(source->length == 0)
    {
        COMPILER_BUG("Empty input\n");
        return false;
    }
    String* out_path = arguments.out_path;
    Token_List* tokens = Lex_tokenize(source, arguments.input_file, arguments.absolute_path);

    if (has_flag(arguments.options, OPT_TOK_OUTPUT))
    {
        String* tok_out = Lex_pretty_print(tokens, allocator);
        if (out_path)
        {
            FILE* temp_file = fopen(out_path->str, "w");
            if (!temp_file)
            {
                fprintf(stderr, "Unable to open temp file: %s\n", out_path->str);
                exit(1);
            }

            string_write_to_file(tok_out, temp_file);
            fclose(temp_file);
        }
        else
        {
            fprintf(stdout, tok_out->str);
        }

        return true;
    }
    
    Parser parser;
    Parser_init(&parser, arguments.absolute_path, tokens, allocator);

    bool result = false;
    if (Parser_parse(&parser, false, allocator))
    {
        if (has_flag(arguments.options, OPT_AST_OUTPUT))
        {
            String* ast = pretty_print_ast(parser.root, allocator);
            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(stderr, "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(ast, temp_file);
                fclose(temp_file);
            }
            else
            {
                fprintf(stdout, ast->str);
            }
            return true;
        }

        Sem_check(parser.root, arguments.absolute_path, allocator);
        
        IR_Program program = IR_translate_ast(parser.root, allocator);
        if (has_flag(arguments.options, OPT_IR_OUTPUT))
        {
            String* IR_out = IR_pretty_print(&program, allocator);
            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(stderr, "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(IR_out, temp_file);
                fclose(temp_file);
            }
            else
            {
                fprintf(stdout, IR_out->str);
            }
            return true;
        }
        
        String* assembly = X64_codegen_ir(&program, allocator);
        if (assembly)
        {           
            if (has_flag(arguments.options, OPT_ASSEMBLY_OUTPUT))
            {
                if (out_path)
                {
                    FILE* temp_file = fopen(out_path->str, "w");
                    if (!temp_file)
                    {
                        fprintf(stderr, "Unable to open temp file: %s\n", out_path->str);
                        exit(1);
                    }
                    
                    string_write_to_file(assembly, temp_file);
                    fclose(temp_file);
                }
                else
                {
                    // @Note: Write out directly to prevent formatting bugs with register names in AT&T.
                    fwrite(assembly->str, 1, assembly->length, stdout);
                }
                return true;
            }
            else
            {
                out_path = create_temp_file(allocator);
            }            
                
            if (out_path)
            {
                FILE* temp_file = fopen(out_path->str, "w");
                if (!temp_file)
                {
                    fprintf(stderr, "Unable to open temp file: %s\n", out_path->str);
                    exit(1);
                }

                string_write_to_file(assembly, temp_file);
                fclose(temp_file);

                String* assembly_out = create_temp_file(allocator);
                result = Compiler_assemble_x86_with_input_file(out_path, assembly_out, allocator);

                if (!result)
                {
                    fprintf(stderr, "Assembler failed\n");
                    exit(1);
                }

                if (!DEFAULT_EXECUTABLE_OUT_PATH)
                {
                    DEFAULT_EXECUTABLE_OUT_PATH = string_allocate("a.out", allocator);
                }
                
                String* executable_out = arguments.out_path ? arguments.out_path : DEFAULT_EXECUTABLE_OUT_PATH;

                result = Compiler_link(assembly_out, executable_out, allocator);

                if (!result)
                {
                    fprintf(stderr, "Linking failed\n");
                    exit(1);
                }
            }
        }
    }
    else
    {
        exit(1);
    }
    
    Parser_free(&parser);
    token_list_free(tokens);

    return result;
}

bool Compiler_compile_file(Compiler_Arguments arguments, Allocator* allocator)
{
    if (!arguments.input_file)
    {
        return false;
    }
    
    FILE* file = fopen(arguments.input_file->str, "r");
    bool result = false;
    if (file)
    {
        String* source = string_create_from_file_with_allocator(file, allocator);
        result = Compiler_compile(source, arguments, allocator);
        fclose(file);
        /* cleanup_temp_files(); */
    }
    return result;
}
