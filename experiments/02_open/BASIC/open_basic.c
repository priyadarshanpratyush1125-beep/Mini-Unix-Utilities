#include <stdio.h> // req for prinf and scanf 
#include <fcntl.h> // req for open() and flags O_RDONLY O_WRONLY etc
#include <unistd.h>// req for File I/O operations(read(),write(),close(),lseek())
                   // req for Process management (fork(),exec(),getpid(),pipe())

int main(void)
{
    int fd;

    fd = open("input.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    printf("fd = %d\n", fd);

    close(fd);

    return 0;
}
