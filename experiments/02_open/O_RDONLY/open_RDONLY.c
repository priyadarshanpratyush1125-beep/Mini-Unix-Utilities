#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd;
    char buffer[20];

    fd = open("log1.txt", O_RDONLY);

    if (fd == -1)
    {
        perror("open");
        return 1;
    }

    int n = read(fd, buffer, 5);

    write(1, buffer, n);  //use for printing on terminal
    //lets write somrthing in read only mode and see what happend 
    ssize_t write_result = write(fd, "pratyush", 8);

    if (write_result == -1)
    {
        // This will now visibly print: "illegal write failed: Bad file descriptor"
        perror("   you are trying to write something in read only mode"); 
    }
    

    close(fd);

    return 0;
}