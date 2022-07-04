all: snake

snake: main.o keysListener.o myfuncs.o snakeHandler.o
	gcc -g -o snake keysListener.o myfuncs.o snakeHandler.o main.o 

main.o: main.c
	gcc -g -c main.c

keysListener.o: keysListener.c keysListener.h
	gcc -g -c keysListener.c

myfuncs.o: myfuncs.c myfuncs.h
	gcc -g -c myfuncs.c

snakeHandler.o: snakeHandler.c snakeHandler.h
	gcc -g -c snakeHandler.c

clean:
	rm ./*.o