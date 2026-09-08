#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
int fd = open(
    "newfile.txt",
    O_WRONLY | O_CREAT,
    0644
);
}