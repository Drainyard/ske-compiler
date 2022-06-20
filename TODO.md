# Bugs
- [x] Bug in IR virtual registers when reallocating the returned register is not marked as in-use

# Improvements
- [ ] Use a simpler grammar syntax in the grammar file

# Features
- [ ] Make codegen more platform agnostic, and put platform specific things somewhere else
- [ ] Use NASM on Windows, and possibly change to Intel syntax on Linux for GAS
- [ ] Fix stack alignment in codegen
- [ ] Possibly move AST definition to an `ast.h` file, and possibly change it to be less union craziness
- [ ] Use *W functions in Win32 when working with files
- [ ] Handle arguments for which compilation step to stop at linker output
- [ ] Add more failing tests
- [ ] Add function calls
- [ ] Add variable bindings (let/var/const?)
- [ ] Add string types
- [ ] Add a type checker stage
- [ ] Add support for windows (and MacOS?)
- [ ] Improve lex and parser error messages (Clang or GCC as examples)
- [ ] Add ARM64 output for M1 and other ARM-based platforms
- [ ] Add verbose mode for stage output (tokenizer/lexer, parser, IR-gen, codegen, etc.)
- [ ] Add global allocator
- [ ] Add different allocator types that are more dynamic than arenas (Something that allows better freeing)
- [ ] Add a CST (Concrete Syntax Tree) stage for better error messages

- [X] Add an OS agnostic layer over platform code
- [X] Add function declarations
- [x] Compile to some IR. Could be basic blocks or some other even more basic assembly IR so we can output to multiple platforms more easily
- [X] Add a few tests (find some way to test code coverage maybe?)
- [X] Add test system with succeeding and failing files testing output
- [X] Rebrand language to Ske Lang and buy ske-lang.org domain
- [X] Change String interface to be more like in https://godbolt.org/z/o7Tn5Kqz3
- [X] Move assemble.sh and link.sh into the compiler script or embed them somehow
- [X] Handle arguments for which compilation step to stop at assembly output
- [X] Handle out file argument
