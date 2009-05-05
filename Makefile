CC = gcc -Wall -ansi -g

all:
	$(CC) gfxinterface.cpp PSOStructures.cpp gfxmath.cpp DeJongFunctions.o -o gfxinterface -lGL -lGLU `sdl-config --cflags --libs`

clean:
	@echo Cleaning up...
	@rm gfxinterface
	@echo Done.
