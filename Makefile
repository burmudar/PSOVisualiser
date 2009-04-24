CC = gcc -Wall -ansi

all:
	$(CC) gfxinterface.cpp PSOStructures.cpp gfxmath.cpp -o gfxinterface -lGL -lGLU `sdl-config --cflags --libs`

clean:
	@echo Cleaning up...
	@rm gfxinterface
	@echo Done.
