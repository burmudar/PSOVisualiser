CC = gcc -Wall -ansi -lstdc++ -lm

all:
	@echo Building via Docker
	docker run -v $(shell pwd):/pso pso-builder make linux-gfx
	@echo Build via Docker Complete

docker-build:
	@echo Building docker image 'pso-builder'
	docker build -t pso-builder .
	@echo Done building docker image 'pso-builder'


linux-gfx:
	@echo Building Graphical PSO for Linux
	$(CC) gfxinterface.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o gfx_unix -lGL -lGLU `sdl-config --cflags --libs`
	@echo Building Graphical PSO for Linux Complete

linux-console:
	@echo Building Console version
	$(CC) PSOMain.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o pso_console_unix -lGL -lGLU `sdl-config --cflags --libs`
	@echo Building Console version Complete

mac-gfx:
	@echo Building for Graphical PSO for Mac
	$(CC) -Wall -ansi -lstdc++ gfxinterface.cpp PSOStructures.cpp gfxstructures.cpp BenchFunctions.cpp -g -o gfx_mac `sdl-config --cflags --libs` -framework OpenGL
	@echo Building for Graphical PSO for Mac Complete

clean:
	@echo Cleaning up...
	@rm gfx_mac
	@rm gfx_unix
	@rm pso_console_unix
	@echo Done.
