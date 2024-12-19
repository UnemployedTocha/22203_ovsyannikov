#include <unistd.h>

void print_hello() {
    write(2, "Hello world!\n", 13);
}

int main() {
    print_hello();
    return 0;
}
