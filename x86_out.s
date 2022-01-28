.data
.text
.global main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $2, %rbx
        movq    $3, %r10
        addq    %rbx, %r10
        movq    %r10, %rax
        popq    %rbp
        ret
