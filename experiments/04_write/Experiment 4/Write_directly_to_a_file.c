#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    char msg[] = "Hello from write() to a file!\n";

    write(fd, msg, sizeof(msg) - 1);

    close(fd);

    return 0;
}