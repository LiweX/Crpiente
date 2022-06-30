#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/mman.h>
#include "keysListener.h"

int main(int argc,char**argv){

    noncanonical_mode(); //switch to non canonical mode (dont need enter to flush stdin) and no echo
    char * direction = (char *)mmap(NULL,1,PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS,-1,0);
    *direction='0';

    printf("This is a snake game\nPress any key to start");
    getchar();
    printf("\e[1;1H\e[2J");//clear terminal
    printf("The game has started\nUse arrow keys to move\n");

    int pid = fork();
    if(pid == 0){
        detectInput(direction);
    }else{
        while(-1){
            char msg[15];
            sprintf(msg,"\rUser press %c",*direction);
            write(1,msg,strlen(msg));
        }
    }
    return 0;
}