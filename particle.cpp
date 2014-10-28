#include <math.h>
#include <stdlib.h>
#include <limits.h>
#define epsilon 0.9501646 //thermal energy?? E = 1/2 mass * velocity^2 lennard jones??
#define mu 4*M_PI*(1/pow(10,7))
#define RAND_MIN 0
#include "vector.hpp"
#include "particle.hpp"

partcl **InitCord(double lowx, double upx, double lowy, 
		double upy, double lowz, double upz, int nPartcl)
{
	partcl **c = new partcl*[nPartcl];
	
	//initialize positions, velocities, and accelerations
	for(int i = 0; i<nPartcl; i++){
		c[i] = new partcl();
		
		c[i]->positionSet(RandVectr( lowx,  upx,  lowy, upy,  lowz,  upz)); 
		c[i]->velocitySet( RandVectr( lowx,  upx,  lowy, upy,  lowz,  upz)); 
		c[i]->orientationSet(RandVectr( lowx,  upx,  lowy, upy,  lowz,  upz)); 
		//between 6-20 nm for diam, mag = (4.5*10^6, diam^3 * pi ) / 3
		c[i]->diam = (double) ( abs( rand() % 20-6)) / pow(10,6);
		c[i]->m =  (double)(abs(rand() % 157-47)) / pow(10,10);
		
		c[i]->accelSet( vectr(0,0,0));
		
	}
	return c;
}

void partcl::positionSet(vectr a)
{
	r = a;
}

void partcl::orientationSet(vectr a)
{
	u = a;
}

void partcl::accelSet(vectr accel)
{
	a = accel;
}

void partcl::velocitySet(vectr a)
{
	v = a;
}

vectr partcl::getPosition()
{
return r;
}

vectr partcl::getVelocity()
{
return v;
}


vectr partcl::getOrientation()
{
return u;
}

vectr partcl::getAcceleration()
{
return a;
}


vectr ComputeDipole(partcl *a, partcl *b)
{
	//seperation(a,b);
	double r1 = a->r.distance(b->r);
	vectr r2 = (a->r - b->r)/r1; 
	vectr accel = (r2*(a->u.dot(b->getOrientation())) + b->getOrientation() *
	(a->u.dot(r2)) + a->getOrientation() * (b->u.dot(r2)) + r2 * -5 * (b->u.dot(r2)) * (a->u.dot(r2)) ) * (3*mu * a->m * b->m) / (4 * M_PI * pow(r1,4));
	return accel;

}

vectr torque(partcl *a, partcl *b)
{

double r1 = a->r.distance(b->r);
vectr r2 = (a->r + b->r * (-1) ) / r1;
vectr torque = (a->u.cross( b->getOrientation() ) * (-1/3) + b->u.cross(r2) * (a->u.dot(r2)) ) * (3*mu * a->m * b->m) / (4 * M_PI * pow(r1,3));
return torque;
} 
//spot to update this ?
void seperation(partcl *a, partcl *b)
{
	double r1 = a->r.distance(b->r);
	vectr r2 = (a->r.VAdd( b->r.Vscalar(-1))).Vscalar( 1/r1);
	double sep = 4*epsilon * (-6*pow((a->diam+b->diam),12) / pow(r1, 15) + 3*pow((a->diam+b->diam),6) / pow(r1, 7) );
	a->positionSet(a->v + (r2*-1*sep));
}


void partcl::print_partcl(FILE *outfile, int i) const
{
	fprintf(outfile, "%d particle\n position: %f\t%f\t%f\n acceleration: %f\t%f\t%f\n orientation: %f\t%f\t%f\n %f\t %f \n",i, r.x, r.y, r.z, a.x, a.y, a.z, u.x, u.y, u.z, m, diam);
}
