CC = gcc -Wall -ansi

all:
	$(CC) gfxinterface.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o gfxinterface -lGL -lGLU `sdl-config --cflags --libs`

clean:
	@echo Cleaning up...
	@rm gfxinterface
	@echo Done.
