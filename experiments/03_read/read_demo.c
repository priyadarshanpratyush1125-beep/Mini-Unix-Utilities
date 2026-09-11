#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[6];

    fd = open("file.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    ssize_t n = read(fd, buffer, 5);

    if (n == -1)
    {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Bytes read = %zd\n", n);

    printf("Data = ");

    for (ssize_t i = 0; i < n; i++)
    {
        printf("%c", buffer[i]);
    }

    printf("\n");

    close(fd);

    return 0;
}