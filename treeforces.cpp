#include <math.h>
#include<stdlib.h>
#include<stdio.h>
#include "vector.hpp"
#include "particle.hpp"
#include "tree.hpp"
#define xi1 3*M_PI*.894
#include <fenv.h> 
#include <time.h>
#include <algorithm>


void SingleStep (double deltaT,int nPartcl, Tree *treePtr,partcl **model, vectr pmin,  vectr pmax, double boundary[6]);
void LeapfrogStep (int part, int nPartcl, double deltaT, partcl **model,double boundary[6]);
void dampForce( int nPartcl, double deltaT, partcl **model,double boundary[6]);
void ComputeForces(partcl *element, vectr pmin, vectr pmax, Tree *treePtr);

int main(int argc, char **argv)
{

  
  //std::vector<partcl *> *results;
	FILE *fp = fopen("filename", "w");
	int  nPartcl, stepCount, stepLimit, i,cycles = 1;
	double deltaT;
	nPartcl = atoi(argv[1]);
	deltaT = atof(argv[2]);
	double boundary[6];
	for(i = 0; i < 6; i++)	boundary[i] = atof(argv[3+i]);
	vectr tl = vectr(boundary[0], boundary[3], boundary[4]);
	vectr tr = vectr(boundary[1], boundary[2], boundary[5]);
	vectr center = (tl+tr)/2;
	vectr half = tr-tl;
	double limit = atof(argv[9]);
	vectr pmin = vectr(1/pow(10,8), 1/pow(10,8), 1/pow(10,8));
	vectr pmax = vectr( limit, limit ,limit );
	stepCount = 0;
	stepLimit = atoi(argv[10]);
	printf("%d", argc);
	partcl **model = InitCord(boundary[0], boundary[1], boundary[2], 
		boundary[3], boundary[4], boundary[5], nPartcl);
	while(cycles)
	{
	Tree *treePtr = new Tree(center, half);
		for(int i = 0; i < nPartcl; i++)
		{	
			treePtr->insert(model[i]);
			model[i]->print_partcl(fp, i);
		}
	SingleStep( deltaT, nPartcl, treePtr, model, pmin,  pmax, boundary);
	if(stepCount >= stepLimit) cycles = 0;	
		stepCount++;
	delete treePtr;
	}
	for(int i = 0; i < nPartcl; i++)
		delete model[i];
	delete[] model;
	fclose(fp);
	return 1;
	
}

void SingleStep (double deltaT,int nPartcl, Tree *treePtr,partcl **model, vectr pmin,  vectr pmax, double boundary[6])
{	
	for(int i = 0; i < nPartcl; i++)
	  ComputeForces(model[i] , pmin,  pmax, treePtr); //acceleration	  
	LeapfrogStep (1, nPartcl, deltaT, model,boundary);
	LeapfrogStep (2, nPartcl, deltaT, model,boundary);
}



void LeapfrogStep (int part, int nPartcl, double deltaT, partcl **model,double boundary[6])
{
	int i;

	if (part == 1) 
	{
		for(i = 0; i<nPartcl; i++) 
		{		
			model[i]->velocitySet(model[i]->getVelocity() + model[i]->getAcceleration() * (0.5 * deltaT));
			model[i]->positionSet(model[i]->getPosition() +  model[i]->getVelocity() * deltaT );
			model[i]->r.wrap(boundary);
			printf("particle %d:\t% f\t% f\t% f\n\n",i, model[i]->r.x, model[i]->r.y, model[i]->r.z);
		}
	}
	else 
	{
		for(i = 0; i<nPartcl; i++) 
			model[i]->velocitySet(model[i]->getVelocity() + model[i]->getAcceleration() * (0.5 * deltaT) );
	}
}

void dampForce( int nPartcl, double deltaT, partcl **model,double boundary[6])
{
int i;
	for(i = 0; i<nPartcl; i++) 
	{		
		model[i]->velocitySet(model[i]->getVelocity() + model[i]->getAcceleration()); //* (1/(xi1*model[i]->diam)));
		model[i]->positionSet(model[i]->getPosition() + model[i]->getVelocity() * deltaT);
		//model[i]->orientationSet(model[i]->u * 1/(xi1 * pow(model[i]->diam,3)));
		model[i]->r.wrap(boundary);
		printf("particle %d:\t% f\t% f\t% f\n\n",i, model[i]->r.x, model[i]->r.y, model[i]->r.z);
	}
}



void ComputeForces(partcl *element, vectr pmin, vectr pmax, Tree *treePtr)
 {
std::vector<partcl *> results2;
vectr pmin2 = element->r - pmin;
vectr pmax2 = element->r + pmax;
//use tree code to find nearest neighbor
treePtr->discPoints( pmin2,  pmax2, results2);
for(std::vector<partcl *>::iterator it = results2.begin(); it != results2.end(); ++it)
		{
			element->accelSet(element->getAcceleration() + ComputeDipole(element, *it)* pow(10,21));
			element->orientationSet(element->getOrientation().cross(torque(element, *it)) * pow(10,21));
		}

}
 
