#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    struct user_regs_struct uregs;
    pid_t pid = fork();

    if(pid == 0) {
        // Tracee
        if(ptrace(PTRACE_TRACEME, 0, 0, 0) == -1) {
            printf("%s ", strerror(errno));
        }
//        write(1, "Another syscall!\n", 13);
        execl("/bin/echo", "Another Syscall!", NULL);
    } else if(pid == -1) {
        perror("Mistake: ");
    }

    else {
        // Tracer
        int status = 0;
        wait(&status);
        while (!WIFEXITED(status)){
                if(ptrace(PTRACE_SYSCALL, pid, 0, 0) == -1) {
                    perror("Mistake: ");
                }
                wait(&status);
                if (WIFSTOPPED(status)) {
                        struct user_regs_struct state;
                        if(ptrace(PTRACE_GETREGS, pid, 0, &state) == -1) {
                            perror("Mistake: ");
                        }
                        int syscallId = state.orig_rax;
                        printf("SYSCALL: %d\n", syscallId);
                }
        }
     }
   
    return 0;
}
