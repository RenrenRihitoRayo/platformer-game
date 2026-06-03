
name = game

all: main.c
	gcc -o $(name) main.c -lraylib -fsanitize=address -g -O0