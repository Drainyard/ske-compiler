.data
.text
.global main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $4, %rbx
        movq    $4, %r10
        movq    %rbx, %rax
        imulq   %r10
        movq    %rax, %r10
        movq    $2, %rbx
        movq    %r10, %rax
        cqo
        idivq   %rbx
        movq    %rax, %rbx
        movq    $20, %r10
        movq    %rbx, %rax
        imulq   %r10
        movq    %rax, %r10
        movq    %r10, %rax
        popq    %rbp
        ret
