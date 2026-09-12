#include <unistd.h>

int main(void)
{
    char msg[] = "ABCDEFGHIJ\n";

    write(1, msg, 5);
    write(1,"\n",1);
    write(1,msg,2);
    write(1,"\n",1);
    write(1,msg,0);
    write(1,"\n",1); 
    write(1,msg,9); 
    write(1,"\n",1);
    write(1,msg,11);
    write(1,"\n",1);
    write(1,msg,12);
    return 0;
}