#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;

    fd = open("log.txt", O_WRONLY | O_APPEND);  // O_APPEND is used when I want new data to be written at the end of the file

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, " Pratyush\n", 8);

    close(fd);

    return 0;
}