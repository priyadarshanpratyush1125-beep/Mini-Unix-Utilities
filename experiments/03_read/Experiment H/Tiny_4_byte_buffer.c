#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[4];
    ssize_t n;
    int read_count = 0;

    fd = open("file.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    while ((n = read(fd, buffer, sizeof(buffer))) > 0)
    {
        read_count++;

        printf("Read %d: %zd bytes -> ", read_count, n);

        write(STDOUT_FILENO, buffer, n);
        write(STDOUT_FILENO, "\n", 1);
    }

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("EOF reached.\n");

    close(fd);

    return 0;
}