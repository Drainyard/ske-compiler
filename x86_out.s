.data
.text
.global main
main:
        pushq %rbp
        movq  %rsp, %rbp
        movq $2, %rbx
        movq $3, %r10
        movq $4, %r11
        movq $1, %r12
        subq %r12, %r11
        movq %r10, %rax
        imulq %r11
        movq %rax, %r11
        addq %rbx, %r11
        movq $12, %rbx
        movq $3, %r10
        movq %rbx, %rax
        cqo
        idivq %r10
        movq %rax, %r10
        addq %r11, %r10
        movq %r10, %rax
        popq %rbp
        ret
