.data
.text
.global main
main:
        pushq %rbp
        movq  %rsp, %rbp
        movq $2, %rbx
        movq $3, %r10
        movq $4, %r11
        movq %r10, %rax
        imulq %r11
        movq %rax, %r11
        addq %rbx, %r11
        movq $2, %rbx
        movq %r11, %rax
        cqo
        idivq %rbx
        movq %rax, %rbx
        movq %rbx, %rax
        popq %rbp
        ret
