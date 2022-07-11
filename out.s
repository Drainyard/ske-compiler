.global main
.global _start
.text
_start:
    xor     %rbp, %rbp
    call    main
    mov     %rax, %rdi
    mov     $60, %rax
    syscall
main:
    push     %rbp
    mov     %rsp, %rbp
    mov     $2, %rbx
    mov     $2, %r10
    cmp     %r10, %rbx
    mov     $3, %r11
    mov     $4, %r12
    cmp     %r12, %r11
    cmp     %r12, %r10
    mov     %r12, %r13
    mov     %r13, %rax
    pop     %rbp
    ret
