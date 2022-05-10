.data
.text
.global main
main:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    $2, %rbx
        movq    $2, %r10
        addq    %rbx, %r10
        movq    %r10, %rax

        #;; fprintf call to output result temporarily
        movq    stderr, %rax
        movq    %r10, %rdx
        movq    $format, %rsi
        movq    %rax, %rdi
        movq    $0, %rax
        call    fprintf
        movq    $0, %rax
        popq    %rbp
        ret
format:
        .asciz "%d\n"
