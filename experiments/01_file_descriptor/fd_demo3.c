#include <unistd.h>

int main(void)
{
    write(1, "this is stdout\n", 15);
    write(2, "this is stderr\n", 15);

    return 0;
}
