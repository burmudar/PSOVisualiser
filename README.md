A Graphical visualiser of the Particle Swarm Optimisation algorithm  written in C++ and SDL

The aim of this program was just to visually see how the algorithm operates on a variety of mathematical benchmark functions.

The algorithm might not be entirely correct in finding some of the optimums, but the visual effect is cool.

The algorithm has the following dependances on Linux which can be installed via apt-get:

- **libsdl-dev**

- **libboost-dev**

To compile the source execute _make_ in the root of the directory. After compilation has completed with no errors, the algorithm can be started by executing _./gfxinterface_

The algorithm has the following dependances on Mac which can be installed with Homebrew:

- **brew install sdl**

- **brew install boost**

To compile the source execute _make mac_ in the root of the directory. After compilation has completed with no errors, the algorithm can be started by executing _./gfx_mac_

Program can be compiled on Linux and Mac OS X 10.8. Tested **2013-04-20**
