#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global_init = 10;

void show_addresses(int* p_local_init) {
    printf("&local_init = %p\n", p_local_init);
    printf("&global_init = %p\n\n", &global_init);
}


void show_values(int local_init) {
    printf("local_init = %d\n", local_init);
    printf("global_init = %d\n\n", global_init);
}

int show_maps() {
  printf("/////////////////////////////// /proc/self/maps\n");
	FILE *file;
	if ((file = fopen("/proc/self/maps", "r")) == NULL) {
		printf("Error: unable to open maps");
		return -1;
	}

	char buffer;
	while(!feof(file)){
		fread(&buffer, 1, 1, file);
		printf("%c", buffer);
	}
	printf("\n\n\n\n");
	fclose(file);

    printf("//////////////////////////////////\n\n");
	return 0;
}

int main(int argc, char** argv) {
    int local_init = 20;
    show_addresses(&local_init);
    
    printf("pid:%d\n", getpid());

    int pid = fork();

    if (pid == 0) {
        printf("/////////////////////////////\n");
        printf("Child proc:\n");
        show_maps();
        int parent_pid = getppid();
        int child_pid = getpid();
        printf("parent pid: %d\n", parent_pid);
        printf("child pid: %d\n\n", child_pid);
        show_values(local_init);
        show_addresses(&local_init);

        local_init = 211;
        global_init = 422;

        show_values(local_init);

        printf("\n\n/////////////////////////////\n");

        exit(5);
    } else {
        sleep(2);
        printf("Parent proc\n");
      sleep(20);
        show_values(local_init);
        //sleep(30);

        int child_status;
        wait(&child_status);
        printf("Child exit code: %d\n", WEXITSTATUS(child_status));
    }
    return 0;
}
