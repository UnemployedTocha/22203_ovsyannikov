#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sched.h>
#include <string.h>
#include <sys/wait.h>

#define PAGE_SIZE 4096
#define REGION_SIZE PAGE_SIZE

void write_to_region(unsigned int *reg) {
    size_t i = 0;
    while(true) {
        //sleep(1);
        reg[i % (PAGE_SIZE / sizeof(unsigned int))] = i;
        i++;
    }
}

void read_from_region(unsigned int *reg) {
    size_t i = 0;
    while(true) {
	  //sleep(2);
        if (reg[i % (REGION_SIZE / sizeof(unsigned int))] != i) {
            printf("Sequence failed at: %ld\n", i);
        } else {
            printf("OK\n") ;
        }

        i++;
    }
}

int main() {
    unsigned int *reg = mmap(NULL, REGION_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (reg == MAP_FAILED) {
        perror("mmap failed\n");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("Fork failed\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        write_to_region(reg);
    } else {
        read_from_region(reg);
    }
    munmap(reg, REGION_SIZE);
    return 0;
}

