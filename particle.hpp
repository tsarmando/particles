#ifndef PARTICLE_H
#define PARTICLE_H
#include <stdio.h>
#include "vector.hpp"

class partcl
{
	public:
		
		partcl(vectr u, vectr r, vectr v,vectr a);
		
		partcl(){};
		//magnetization intensity particle diameter
		double m, diam; 
		//orientation of magnet, position vector, initial velocity
		//acceleration
		vectr u, r, v, a;

		
		void positionSet(vectr a);
		void orientationSet(vectr a);
		void accelSet(vectr accel);
		void velocitySet(vectr a);
		vectr getOrientation();
		vectr getAcceleration();
		vectr getPosition();
		vectr getVelocity();
		void print_partcl(FILE *outfile, int i) const;
		
}; 


vectr ComputeDipole(partcl *a, partcl *b); 
vectr torque(partcl *a, partcl *b);  
void seperation(partcl *a, partcl *b); 
partcl **InitCord(double lowx, double upx, double lowy, 
	double upy, double lowz, double upz, int nPartcl);
		
#endif
