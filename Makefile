all:
	gcc test.c mleocomp.c -lm -o test.o
	clear
	./test.o