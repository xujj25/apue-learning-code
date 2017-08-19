#include "apue.h"
#include <sys/wait.h>

int main(void) {
    pid_t pid;

    if ((pid = fork()) < 0) {
        err_sys("fork error");
    } else if (pid == 0) {  // first child
        if ((pid = fork()) < 0) {
            err_sys("fork error");            
        } else if (pid > 0) {
            printf("first child log\n");
            exit(0); // parent from second fork == first child
        }
        
        // second child part: 
        sleep(10);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)  // wait for first child
        err_sys("waitpid error");
    printf("parent proc log\n");

    exit(0);
}