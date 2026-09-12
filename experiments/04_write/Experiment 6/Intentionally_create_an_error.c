#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(void)
{
    int fd = open("output.txt", O_RDONLY | O_CREAT | O_TRUNC); //only open in read mode 

    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    char msg[] = "Hello\n";

    ssize_t n = write(fd, msg, sizeof(msg) - 1);   //since it open in readonly mode so we cannt write in it

    if (n < 0)
        perror("write");

    close(fd);

    return 0;
}