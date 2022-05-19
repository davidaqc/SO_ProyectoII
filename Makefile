all: build

build:
	gcc -c main.c -lpthread
	gcc -o principal main.o -lpthread
	./principal
