#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#define RAND_MIN 0
#include "vector.hpp"


vectr::vectr()
{
	x = y = z = 0;
}


vectr::vectr(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

double vectr::dot(const vectr &b) const
{
	return (x * b.x + y * b.y + z * b.z);
}

double vectr::norm(){
	return sqrt(dot(*this));
}

double vectr::distance(vectr b)
{
	return sqrt(pow(x - b.x,2)+ pow( y - b.y,2) + pow( z - b.z, 2 ));
}


vectr vectr::operator*(double f) const
{
	return vectr(x*f,y*f,z*f);
}

vectr vectr::operator/(double f) const
{
	return *this * (1/f);
}

vectr vectr::operator-(const vectr &b) const
{
	return *this+ b * -1.0;
}

vectr vectr::operator+(const vectr &b) const
{
	double x1, y1, z1;
	x1 = x + b.x;
	y1 = y +b.y;
	z1 = z + b.z;
	return vectr(x1,y1,z1);
}

vectr vectr::VAdd(vectr b)
{
		x += b.x;
		y += b.y;
		z += b.z;
	return *this;
}

static double wrapper(double x, double min, double max)
{
	double len = max - min;
	while(x < min)
		x += len;
	while(x > max)
		x -= len;
	return x;
}
void vectr::wrap(double boundary[6])
{
	x = wrapper(x, boundary[0], boundary[1]);
	y = wrapper(y, boundary[2], boundary[3]);
	z = wrapper(z, boundary[4], boundary[5]);
}

void vectr::collision(vectr x, vectr y)
{

}

vectr vectr::Vscalar(double b)
{
		x *=b;
		y *=b;
		z *=b;
	return *this;
}
//Create a vector inside the system
vectr RandVectr(double lowx, double upx, double lowy, 
		double upy, double lowz, double upz)
{

	//how to create random vector within given limits
	double x =  lowx +  (upx - lowx) * (double)(rand()-RAND_MIN) / (RAND_MAX-RAND_MIN);
	//printf("%d\n" , lowx);
	double y = lowy +  (upy - lowy) * (double)(rand()-RAND_MIN) / (RAND_MAX-RAND_MIN);
	double z = lowz +  (upz - lowz)* (double)(rand()-RAND_MIN) / (RAND_MAX-RAND_MIN);
	return vectr(x, y, z);
}

vectr vectr::cross(const vectr &b ) const
{

	double x1, y1, z1;
	x1 = y * b.z - z * b.y;
	y1 = -1 * (x * b.z - z * b.x);
	z1 = x * b.y - y * b.x;
	return vectr(x1,y1,z1);
	
}

