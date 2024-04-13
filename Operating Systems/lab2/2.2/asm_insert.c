#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

ssize_t mywrite(int fd, const void* buf, size_t count) {
    asm volatile("movq	-24(%rbp), %rcx\n\t"
                "movq	-16(%rbp), %rdx\n\t"
                "movl	-4(%rbp), %eax\n\t"
                "movl	%eax, %esi\n\t"
                "movl	$1, %edi\n\t"
                "movl	$0, %eax\n\t"
                "call	syscall\n\t"
                "leave\n\t"
                "ret");
}

int main() {
    int output = mywrite(1, "Hello world\n", 13);
    printf("output = %d: %s, \n", output, strerror(errno));
    return 0;
}
