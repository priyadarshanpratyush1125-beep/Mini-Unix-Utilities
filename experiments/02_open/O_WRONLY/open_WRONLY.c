#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;

    fd = open("log2.txt", O_WRONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    write(fd, "Pratyush", 8);
    printf("sucessfully write text");
    //now lets see what happend when read something in write only mode
    char buffer[10];
    ssize_t bytes_read = read(fd, buffer, 5);
    if(bytes_read==-1){
        printf("since it is Write only mode so you can not read");
    }
   
    close(fd);

    return 0;
}
