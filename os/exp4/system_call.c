#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pid, pid1 , pid2;
    pid = fork();
    if(pid == -1) {
        printf("Error in Process Creation\n");
        exit(1);
    }
    if(pid!=0) {
        pid1 = getpid();
        printf("Parent Process ID: %d\n", pid1);
        wait(NULL);
        printf("Child terminated\n");  
    }
    else {
        pid2 = getpid();
        printf("Child Process ID: %d\n", pid2);
    }
    return 0;
}