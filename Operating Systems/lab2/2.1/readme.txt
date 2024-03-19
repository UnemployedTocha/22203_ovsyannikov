gcc print_hello.c -o print_hello
strace ./print_hello

gcc hello_with_write.c -o hello_with_write
strace ./hello_with_write

gcc my_write.c -o my_write
strace ./my_write

strace -c wget kernel.org
