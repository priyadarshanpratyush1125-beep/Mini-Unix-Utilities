#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    // 1. Correctly open the file. O_TRUNC will wipe it to 0 bytes.
    int fd = open("test.txt", O_RDWR | O_TRUNC);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    char buffer[20];
    ssize_t x = read(fd, buffer, 8);

    if (x == -1) 
    {
        perror("read failed");
    }
    else if (x == 0)
    {
        // 3. Added the missing semicolon
        printf("file became empty\n");
    }
    else 
    {
        printf("Read %ld bytes\n", x);
    }

    close(fd);
    return 0;
}
