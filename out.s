.global main
.global _start
.text
_start:
    xor     %rbp, %rbp
    call    main
    movq     %rax, %rdi
    movq     $60, %rax
    syscall
main:
    pushq     %rbp
    movq     %rsp, %rbp
    movq     $2, %rbx
    movq     $2, %r10
    movq     %rbx, %rax
    cmp     %r10, %rax
    sete    %al
    movb     %al, -1(%rbp)
    movq     -1(%rbp), %rbx
    movq     %rbx, %rax
    popq     %rbp
    ret
