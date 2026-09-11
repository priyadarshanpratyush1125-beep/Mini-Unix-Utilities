#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[10];
    ssize_t n;

    fd = open("empty.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    n = read(fd, buffer, sizeof(buffer));

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("read() returned: %zd\n", n);

    close(fd);

    return 0;
}