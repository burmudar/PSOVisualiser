CC = gcc -Wall -ansi -lstdc++

all:
	@echo Building Graphical PSO for Linux
	$(CC) gfxinterface.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o gfx_unix -lGL -lGLU `sdl-config --cflags --libs`
	@echo Building Graphical PSO for Linux Complete

console:
	@echo Building Console version
	$(CC) PSOMain.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o pso_console_unix -lGL -lGLU `sdl-config --cflags --libs`
	@echo Building Console version Complete

mac:
	@echo Building for Graphical PSO for Mac
	$(CC) -Wall -ansi -lstdc++ gfxinterface.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o gfx_mac `sdl-config --cflags --libs` -framework OpenGL
	@echo Building for Graphical PSO for Mac Complete

clean:
	@echo Cleaning up...
	@rm gfx_mac
	@rm gfx_unix
	@rm pso_console_unix
	@echo Done.
