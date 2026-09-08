#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;

    fd = open("log2.txt", O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, "Pratyush", 8);

    close(fd);

    return 0;
}