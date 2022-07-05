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

int main(int argc, char **argv)
{

    srand(time(NULL));
    noncanonical_mode();
    int *map = (int *)mmap(NULL, sizeof(int) * 24 * 80, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    Serpiente *snake = (Serpiente *)mmap(NULL, sizeof(Serpiente), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *apple = mmap(NULL, sizeof(int) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    int *direction = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    init_map(map);
    snakeInit(snake);
    randomApple(apple);
    drawApple(apple, map);
    drawSnake(map, snake);
    printf("This is a snake game\nPress any key to start");
    getchar();
    system("clear");
    printf("The game has started\nUse arrow keys to move\n");
    sleep(1);

    int pid = fork();
    if (pid == 0)
    {
        inputHandler(direction); // child encargado de detectar input    pid = fork();
    }
    pid = fork();
    if (pid == 0)
    {
        int growflag = 0;
        int prevTailPos[2];
        while (-1)
        {
            usleep(100000);
            snakeHandler(snake, direction);
            if (growflag)
            {
                addNode(snake, prevTailPos[0], prevTailPos[1]);
                growflag = 0;
            }
            init_map(map);
            if (checkApple(apple, snake))
            {
                prevTailPos[0] = snake->cola->x;
                prevTailPos[1] = snake->cola->y;
                randomApple(apple);
                growflag = 1;
            }
            drawApple(apple, map);
            drawSnake(map, snake);
            print_map(map);
        }
    }
    while (-1);
    return 0;
}
