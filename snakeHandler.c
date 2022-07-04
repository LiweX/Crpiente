#include <unistd.h>
#include <stdlib.h>
#include "myfuncs.h"
#include "snakeHandler.h"

void snakeHandler(Serpiente* snake,int *direction){
    Nodo* pivot = snake->cola;
    while(pivot->prev!=NULL){
        pivot->x=pivot->prev->x;
        pivot->y=pivot->prev->y;
        pivot=pivot->prev;
    }
    switch (*direction)
    {
    case HEAD_UP:
        snake->cabeza->x--;
        break;
    case HEAD_DOWN:
        snake->cabeza->x++;
        break;
    case HEAD_RIGHT:
        snake->cabeza->y++;
        break;
    case HEAD_LEFT:
        snake->cabeza->y--;
        break;
    default:
        break;
    }
}

void drawSnake(int*map,Serpiente* snake){
    Nodo* pivot = snake->cabeza;
    map[pivot->y*24+pivot->x] = 2;
    pivot = pivot->next;
    while(pivot->next!=NULL){
        map[pivot->y*24+pivot->x] = 3;
        pivot = pivot->next;
    }
    map[pivot->y*24+pivot->x] = 4;
}

void snakeInit(Serpiente* serpiente){
    Nodo* cabeza = (Nodo*)malloc(sizeof(Nodo));
    Nodo* cuerpo = (Nodo*)malloc(sizeof(Nodo));
    Nodo* cola = (Nodo*)malloc(sizeof(Nodo));
    cabeza->x=10;
    cabeza->y=10;
    cabeza->type=HEAD_UP;
    cabeza->next=cuerpo;
    cabeza->prev=NULL;
    cuerpo->x=10;
    cuerpo->y=11;
    cuerpo->type=BODY_STRAIGHT_V;
    cuerpo->next=cola;
    cuerpo->prev=cabeza;
    cola->x=10;
    cola->y=12;
    cola->next=NULL;
    cola->prev=cuerpo;
    cola->type=TAIL_UP;
    serpiente->cabeza=cabeza;
    serpiente->cola=cola;
    serpiente->size=3;
}

void addNode(Serpiente* serpiente,int x,int y){
    Nodo* newNode = (Nodo*)malloc(sizeof(Nodo));
    newNode->next=NULL;
    newNode->prev=serpiente->cola;
    newNode->x=x;
    newNode->y=y;
    serpiente->cola->next=newNode;
    serpiente->cola=newNode;
    serpiente->size=serpiente->size++;
}

void checkApple(int *apple,Serpiente *snake,int*map){
    while(-1){
        if(snake->cabeza->x==apple[0]&&snake->cabeza->y==apple[1]){
            map[snake->cabeza->y*24+snake->cabeza->x]=0;
            randomApple(apple);
            drawApple(apple,map);
        }
    }
}