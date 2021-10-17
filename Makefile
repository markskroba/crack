all: crack.c
	gcc -o crack crack.c -lpthread -lcrypt