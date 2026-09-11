#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[100];
    ssize_t n;

    fd = open("file.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    n = read(fd, buffer, 5);

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("read() returned: %zd\n", n);

    write(STDOUT_FILENO, buffer, n);

    close(fd);

    return 0;
}