#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 4096

int main(int argc, char *argv[])
{
    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    /* Check command-line arguments */
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    /* Open the file */
    fd = open(argv[1], O_RDONLY);

    if (fd == -1)
    {
        perror("mycat: open");
        return 1;
    }

    /* Read and write until EOF */
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        ssize_t total_written = 0;

        while (total_written < bytes_read)
        {
            ssize_t bytes_written;

            bytes_written = write(
                STDOUT_FILENO,
                buffer + total_written,
                bytes_read - total_written
            );

            if (bytes_written == -1)
            {
                perror("mycat: write");
                close(fd);
                return 1;
            }

            total_written += bytes_written;
        }
    }

    /* Check read error */
    if (bytes_read == -1)
    {
        perror("mycat: read");
        close(fd);
        return 1;
    }

    /* Close file */
    if (close(fd) == -1)
    {
        perror("mycat: close");
        return 1;
    }

    return 0;
}