#include <unistd.h>  // Required for the write() system call 

int main(void)
{
    write(1, "Hello from stdout\n", 18);  //synatx is ssize_t bytesWritten = write(int fd, const void *buf, size_t count);


    return 0;
}
