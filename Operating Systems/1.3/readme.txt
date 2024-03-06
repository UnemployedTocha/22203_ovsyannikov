gcc -c hello_from_shared_lib.c -fPIC -o hello_from_shared_lib.o

gcc hello_from_shared_lib.o -shared -o my_shared_lib.so

rm hello_from_shared_lib.o

gcc hello3.c -o hello3 -l:my_shared_lib.so -L.

export LD_LIBRARY_PATH=.

./hello3
