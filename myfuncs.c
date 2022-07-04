#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "myfuncs.h"

void randomApple(int *apple){
    apple[0] = rand() % 80;
    apple[1] = rand() % 24;
}

void drawApple(int *apple,int*map){
    map[apple[0]*24 + apple[1]]=1;
}

int **alloc_matrix(int XDIM, int YDIM)
{
    int **array;
    array = malloc(sizeof(int*)*(size_t)YDIM);
    for(int i = 0 ; i < YDIM ; i++)
        array[i] = malloc( sizeof(int) *(size_t)XDIM);
    return array;
}

void init_map(int*map){
    for(int i=0;i<24;i++)
        for(int j=0;j<80;j++)
            map[j*24+i]=0;
}

void print_map(int*map){
    char string[(24*81)+1];
    char aux[2];
    bzero(string,(24*81)+1);
    bzero(aux,2);
    int x1=0,y1=0,x2=0,y2=0;
    for(int i=0;i<24;i++){
        for(int j=0;j<80;j++){
            switch (map[j*24+i])
            {
            case 0:
                strcat(string," \0");
                break;
            case 1:
                strcat(string,"o\0");
                x1=j;
                y1=i;
                break;
            case 2:
                strcat(string,"@\0");
                x2=j;
                y2=i;
                break;
            case 3:
                strcat(string,"#\0");
                break;
            case 4:
                strcat(string,"+\0");
                break;                           
            default:
                break;
            }
        }
        strcat(string,"\n");
    }
    strcat(string,"\0");
    system("clear");
    write(1,string,strlen(string));
    printf("\nmanzana=(%d,%d),cabeza(%d,%d)",x1,y1,x2,y2);
}