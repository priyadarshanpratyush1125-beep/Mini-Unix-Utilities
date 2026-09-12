#include <unistd.h>

int main(void)
{
    char message[] = "Normal output\n";
    char error[] = "Error output\n";

    write(1, message, sizeof(message) - 1);
    write(2, error, sizeof(error) - 1);

    return 0;
}