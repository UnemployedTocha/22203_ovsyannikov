#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char *env = getenv("NAME");
    printf("%s\n", env);

    setenv("NAME", "ENV!", 1);
    env = getenv("NAME");
    printf("%s\n", env);
}
