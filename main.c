#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>

#include "keysListener.h"
#include "myfuncs.h"
#include "snakeHandler.h"


int main(int argc,char**argv){
    srand(time(NULL));
    noncanonical_mode();
    int * map=(int *)mmap(NULL,sizeof(int)*24*80,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    Serpiente * snake=(Serpiente *)mmap(NULL,sizeof(Serpiente),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    int *apple=mmap(NULL,sizeof(int)*2,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    int *direction=mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    init_map(map);
    snakeInit(snake);
    randomApple(apple);
    drawApple(apple,map);
    drawSnake(map,snake);
    printf("This is a snake game\nPress any key to start");
    getchar();
    system("clear");
    printf("The game has started\nUse arrow keys to move\n");
    sleep(1);

    int pid = fork();
    if(pid == 0){
        inputHandler(direction);
    }
    pid = fork();
    if(pid==0){
        while(-1){
            usleep(100000);
            snakeHandler(snake,direction);
            init_map(map);
            drawApple(apple,map);
            drawSnake(map,snake);
            print_map(map);
        }
    }
    pid = fork();
    if(pid==0){
        checkApple(apple,snake,map);
    }
        while(-1){
            //usleep(100000);
           
        }
    return 0;
}
    
