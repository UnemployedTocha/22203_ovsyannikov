#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

ssize_t mywrite(int fd, const void* buf, size_t count) {
    return syscall(SYS_write, fd, buf, count);
}

int main() {
    int output = mywrite(1, "Hello world\n", 13);
    printf("output = %d: %s, \n", output, strerror(errno));
    return 0;
}
