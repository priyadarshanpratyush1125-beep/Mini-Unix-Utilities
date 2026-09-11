#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[10];
    ssize_t n;

    fd = open("file.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(STDOUT_FILENO, buffer, n);
    }

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}