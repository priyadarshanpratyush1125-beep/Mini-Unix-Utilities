#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[20];

    fd = open("log1.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    int n = read(fd, buffer, 5);

    write(1, buffer, n);

    close(fd);

    return 0;
}