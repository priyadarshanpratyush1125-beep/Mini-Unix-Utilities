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

    n = read(fd, buffer, 10);

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("First read: %zd bytes\n", n);
    write(STDOUT_FILENO, buffer, n);
    write(STDOUT_FILENO, "\n", 1);

    n = read(fd, buffer, 10);

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Second read: %zd bytes\n", n);
    write(STDOUT_FILENO, buffer, n);
    write(STDOUT_FILENO, "\n", 1);

    close(fd);

    return 0;
}