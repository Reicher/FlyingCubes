# Makefile for FlyingCubes
CC=g++
CFLAGS=`sdl-config --cflags` -c 
LFLAGS=`sdl-config --libs` -o

all: main.o FlyingCube.o Morph.o Helpers.o GPIOClass.o BlinkLED.o Button.o
	$(CC) $(LFLAGS) FlyingCubes main.o FlyingCube.o Morph.o Helpers.o GPIOClass.o BlinkLED.o Button.o
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
FlyingCube.o: FlyingCube.cpp FlyingCube.h
	$(CC) $(CFLAGS) FlyingCube.cpp
Morph.o: Morph.cpp Morph.h
	$(CC) $(CFLAGS) Morph.cpp
Helpers.o: Helpers.cpp Helpers.h
	$(CC) $(CFLAGS) Helpers.cpp
GPIOClass.o: GPIOClass.cpp GPIOClass.h
	$(CC) $(CFLAGS) GPIOClass.cpp
BlinkLED.o: BlinkLED.cpp BlinkLED.h
	$(CC) $(CFLAGS) BlinkLED.cpp  
Button.o: Button.cpp Button.h
	$(CC) $(CFLAGS) Button.cpp
clean: 
	rm -rf *.o FlyingCubes
