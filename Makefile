all: crack_genpwds.c
	gcc -o crack crack_genpwds.c -lpthread -lcrypt