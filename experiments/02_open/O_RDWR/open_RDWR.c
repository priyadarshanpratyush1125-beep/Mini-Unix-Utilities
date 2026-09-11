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

    ssize_t n = read(fd, buffer, 5);

    write(1, buffer, n);  // write on terminal means read test written inside log3.txt

    write(fd, "Pratyush", 8); // write inside log3.txt

    close(fd);

    return 0;
}