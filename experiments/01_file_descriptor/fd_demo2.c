#include <unistd.h>

int main(void)
{
    write(1, "Hello from stdout\n", 18);

    return 0;
}
