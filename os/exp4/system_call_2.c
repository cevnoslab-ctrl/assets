#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    printf("Program Started\n");   
    int fd = open("demo.txt", O_CREAT | O_WRONLY, 0644);
    pid_t pid = fork();
    if(pid==0) {
        printf("Child Process Created\n");
        printf("child pid = %d\n", getpid());
        close(fd);
        printf("child clos ed file\n");
        printf("child terminated\n");
        exit(0);
    }
    else {
        printf("Parent Process\n");
        printf("parent pid = %d\n", getpid());
        close(fd);
        printf("parent closed\n");
        printf("parent terminated\n");
        exit(0);
    }
    
}