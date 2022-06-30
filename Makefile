all: snake

snake: main.o keysListener.o
	gcc -o snake keysListener.o main.o 

main.o: main.c
	gcc -c main.c

keysListener.o: keysListener.c keysListener.h
	gcc -c keysListener.c
