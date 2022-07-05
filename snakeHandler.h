#define HEAD_UP         1
#define HEAD_DOWN       2
#define HEAD_LEFT       3
#define HEAD_RIGHT      4
#define BODY_STRAIGHT_V 5
#define BODY_STRAIGHT_H 6
#define LEFT_UP_BODY    7
#define RIGHT_UP_BODY   8
#define LEFT_DOWN_BODY  9
#define RIGHT_DOWN_BODY 10
#define TAIL_UP         11
#define TAIL_DOWN       12
#define TAIL_LEFT       13
#define TAIL_RIGHT      14

typedef struct Nodo{
    int type;
    int x,y;
    struct Nodo* next;
    struct Nodo* prev;
}Nodo;

typedef struct Serpiente{
    Nodo* cabeza;
    Nodo* cola;
    int size;
}Serpiente;

void snakeHandler(Serpiente* snake,int *direction);
void drawSnake(int*map,Serpiente* snake);
void snakeInit(Serpiente* lista);
void addNode(Serpiente* lista,int x,int y);
int checkApple(int *apple,Serpiente*snake);