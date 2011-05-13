CC = gcc -Wall -ansi

all:
	$(CC) gfxinterface.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o gfxinterface -lGL -lGLU `sdl-config --cflags --libs`

mac:
	@echo Building for Mac
	$(CC) gfxinterface.cpp -g -o gfxinterface `sdl-config --cflags --libs` -I /opt/local/include/ -I . -framework OpenGL
	@echo Building for Mac Complete

clean:
	@echo Cleaning up...
	@rm gfxinterface
	@echo Done.
