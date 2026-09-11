#include <unistd.h> // Required for the write() system call 
int main(void)
{
    write(1, "this is stdout\n", 15);   //synatx is ssize_t bytesWritten = write(int fd, const void *buf, size_t count);

    write(2, "this is stderr\n", 15);

    return 0;
}
