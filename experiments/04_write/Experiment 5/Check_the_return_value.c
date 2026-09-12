#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd < 0){
        return 1;
    }
    char msg[] = "Hello Pratyush\n";

    ssize_t n = write(fd, msg, sizeof(msg) - 1);

    if (n < 0)
    {
        close(fd);
        return 1;
    }

    close(fd);

    return 0;
}