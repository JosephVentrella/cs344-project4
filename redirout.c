#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char *buf[2048];

int main(int argc, char *argv[])
{
    if(argc > 2) {
        int fd = open(argv[1], O_RDWR | O_CREAT |O_TRUNC, 0666);
        int fds[2];
        pipe(fds);
        pid_t pid = fork();

        if(pid) {
            dup2(fds[1], 1); 
            close(fds[0]);
            execvp(argv[2], argv + 2);
        }
        close(fds[1]);
        int output = read(fds[0], buf, sizeof buf);
        write(fd, buf, output);
        close(fds[0]);
        close(fd);
    }
    else{
        perror("No commands specified to write");
        exit(1);
    }

}