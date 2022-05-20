all: build

build:
	gcc `pkg-config --cflags gtk+-3.0` -c  matriz_logica.c `pkg-config --libs gtk+-3.0`
	gcc `pkg-config --cflags gtk+-3.0` -o UI  Ui.c -lpthread `pkg-config --libs gtk+-3.0` -export-dynamic
	./UI
