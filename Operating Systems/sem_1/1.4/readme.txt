gcc -c hello_from_shared_dyn_lib.c -fPIC -o hello_from_shared_dyn_lib.o

gcc -shared hello_from_shared_dyn_lib.o -o my_shared_lib.so

rm hello_from_shared_dyn_lib.o

gcc hello4.c -o hello4

./hello4
