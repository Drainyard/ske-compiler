# Bugs
- [ ] Bug in x86 codegen for functions. If return statement is missing (for any function) pop and ret won't be emitted
- [ ] Handle dynamic arrays better in IR. Currently can't reallocate because I (stupidly) use pointers everywhere...
- [ ] Returning nothing from 'main' will return a garbage exit code.

- [x] Bug in IR virtual registers when reallocating the returned register is not marked as in-use
- [x] Fix bug where 'rbx' register was accidentally output as 'rax' (both Intel and AT&T)

# Improvements
- [ ] Use a simpler grammar syntax in the grammar file
- [x] Possibly change prefixes to uppercase (i.e. Parser_, IR_, X86_, Lex_)

# Features
- [ ] Add the possibility to take intermediate pass output as input and compile from there (tokens->ast->ir)
- [ ] Make codegen more platform agnostic, and put platform specific things somewhere else
- [ ] Use NASM on Windows, and possibly change to Intel syntax on Linux for GAS
- [ ] Fix stack alignment in codegen
- [ ] Write a Hello, World! program in Ske
- [ ] Use *W functions in Win32 when working with files
- [ ] Handle arguments for which compilation step to stop at linker output
- [ ] Add more failing tests
- [ ] Add function calls with args
- [ ] Add variable bindings (:: and :=?)
- [ ] Add binary comparison operators (==, !=, >, <, <=, >=)
- [ ] Add unary not
- [ ] Add short circuiting to || and &&
- [ ] Add string types
- [ ] Add a type checker stage
- [ ] Add support for windows (and MacOS?)
- [ ] Improve lex and parser error messages (Clang or GCC as examples)
- [ ] Add ARM64 output for M1 and other ARM-based platforms
- [ ] Add global allocator
- [ ] Add different allocator types that are more dynamic than arenas (Something that allows better freeing)
- [ ] Add a CST (Concrete Syntax Tree) stage for better error messages
- [ ] Consider changing AST to be less union craziness


- [x] Change headers-only to be a single h and c file per pass
- [x] Add verbose mode for stage output (tokenizer/lexer, parser, IR-gen, codegen, etc.)
- [x] Add function calls with zero args
- [x] Possibly move AST definition to an `ast.h` file
- [x] Add an OS agnostic layer over platform code
- [x] Add function declarations
- [x] Compile to some IR. Could be basic blocks or some other even more basic assembly IR so we can output to multiple platforms more easily
- [x] Add a few tests (find some way to test code coverage maybe?)
- [x] Add test system with succeeding and failing files testing output
- [x] Rebrand language to Ske Lang and buy ske-lang.org domain
- [x] Change String interface to be more like in https://godbolt.org/z/o7Tn5Kqz3
- [x] Move assemble.sh and link.sh into the compiler script or embed them somehow
- [x] Handle arguments for which compilation step to stop at assembly output
- [x] Handle out file argument
