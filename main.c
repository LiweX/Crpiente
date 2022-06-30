#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include "keysListener.h"

int main(int argc,char**argv){
    noncanonical_mode(); //switch to non canonical mode (dont need enter to flush stdin) and no echo
    printf("This is a snake game\nPress any key to start");
    getchar();
    printf("\e[1;1H\e[2J");//clear terminal
    printf("The game has started\nUse arrow keys to move\n");
    detectInput();
    return 0;
}