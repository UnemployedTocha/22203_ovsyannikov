#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    char *env = getenv("NAME");

    if (env != NULL) {
        printf("%s\n", env);
    } else {
        printf("Environment variable 'NAME' not set.\n");
    }

    setenv("NAME", "ENV!", 1);
    env = getenv("NAME");
    if (env != NULL) {
        printf("%s\n", env);
    } else {
        printf("Failed to set environment variable 'NAME'.\n");
    }

    return 0;
}
