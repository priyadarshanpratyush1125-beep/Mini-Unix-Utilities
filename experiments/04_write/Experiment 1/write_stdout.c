#include<unistd.h>
#include<string.h>
int main(void){
    char msg[9]="PRATYUSH\n";  //PRATYUSH -->8bytes where /n takes 1 byte so i take size=9
    write(1,msg,5);            
    write(1,msg,strlen,3);
    /*now i have doubt that when i first call write() then offset should be move to 5 then i again call write() 
     it should move (offset 5 to 8) and print USH */

    /* NOTE--> i am not uising FD here so for every write() it start from P */
    return 0;
}