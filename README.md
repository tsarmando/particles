A Ferrofluid Simulation
=========

This is a simulation of single domain nano-particles inside a non-magnetic solvent.

The arguments for the program are:

1. An Whole number for the number of particles
2. A positive real for time step size
3. Six, real, end points representing the x,y,z lower and upper bounds. For example the cube centered at the orgin is given as: -1 1 -1 1 -1 1
4. The max distance a point can interact with another point
5. The number of steps

An example would be 

./forces 100 .5 -1 1 -1 1 -1 1 1 10
