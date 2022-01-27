.data
.text
.global main
main:
        pushq %rbp
        movq  %rsp, %rbp
        movq $2, %rbx
        movq $6, %r10
        addq %rbx, %r10
        movq $3, %rbx
        movq $4, %r11
        addq %rbx, %r11
        addq %r10, %r11
        movq $4, %rbx
        addq %r11, %rbx
        movq %rbx, %rax
        popq %rbp
        ret
