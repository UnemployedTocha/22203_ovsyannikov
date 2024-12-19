gcc -c hello_from_static_lib.c -o hello_from_static_lib.o

arr r my_static_lib.a hello_from_static_lib.o

rm hello_from_static_lib.o

gcc hello2.c -l:my_static_lib.a -L. -o hello2

./hello2
