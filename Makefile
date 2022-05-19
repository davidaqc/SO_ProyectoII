all: build

build:
	gcc -c main2.c -lpthread
	gcc -o principal2 main2.o -lpthread
	./principal
