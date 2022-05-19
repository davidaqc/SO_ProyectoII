all: build

build:
	gcc -c main2.c -lpthread
	gcc -o principal main.o -lpthread
	./principal
