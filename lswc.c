#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


#define READ 0
#define WRITE 1

int main(int argc, char const *argv[]){
  
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if(pid ==0)
    {
        close(1);
        dup2(fd[WRITE],1);
        close(fd[0]);
        execlp("ls","ls", "-1a", argv[1],NULL);
        perror("execlp");
        exit(1);
    }
    else
    {
        close(0);
        dup2(fd[READ],0);        
        close(fd[1]);         
        execlp("wc","wc", "-l",NULL);
        perror("execlp");
        exit(1);
    }
}