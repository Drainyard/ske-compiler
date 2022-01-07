	.global _start

.data
message:
	.asciz	"Hello, calculator!\n"
	len =. - $msg
	
	.text
_start:
	# write(1, message, $len)
	mov	$1, %rax
	mov $1, %rdi
	mov $message, %rsi
	mov $19, %rdx
	syscall

	# exit(0)
	mov	$60, %rax
	xor %rdi, %rdi
	syscall

	
