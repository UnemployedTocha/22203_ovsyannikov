gcc hello_world.c -o hello_world
strace ./hello_world

gcc hello_with_write.c -o hello_with_write
strace ./hello_with_write

gcc my_write.c -o my_write
strace ./my_write

strace -c wget kernel.org
