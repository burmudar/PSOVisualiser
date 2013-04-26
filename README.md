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

The program responds to the following keyboard shortcuts:

- **F1** : Clears the chart and disables/enables drawing of the particles
- **F2** : Disables/Enables the drawing the personal best of each particle (best particles are coloured white)
- **F3** : Disables/Enables the drawing the current position of each particle
- **F4** : Reset the algorithm and advances to the next function
- **F5** : Reinitialises the algorithm with the standard PSO
- **F6** : Reinitialises the algorithm with the PSO that uses Inertia
- **F7** : Reinitialises the algorithm with the PSO that uses Constriction Coefficient
- **F8** : Resets the view perspective to the default for the current benchmark
- **F12**: Changes the shape the particles use
- **a** : Moves view point left
- **d** : Moves view point right
- **w** : Moves view point forward
- **s** : Moves view point backward

In addtion to the keyboard the mouse can be used the "Look around". One can also zoom in and out with the mousewheel.

TODO:
=====

- Rewrite gfxinterface.cpp to be more OO and less procedural
- Add test cases
