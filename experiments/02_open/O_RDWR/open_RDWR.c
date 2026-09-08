#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[10];

    fd = open("log3.txt", O_RDWR);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    int n = read(fd, buffer, 5);

    write(1, buffer, n);

    write(fd, "Pratyush", 8);

    close(fd);

    return 0;
}