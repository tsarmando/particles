#ifndef VECTOR_H
#define VECTOR_H

#define mu 4*M_PI*(1/pow(10,7))
class vectr;
class vectr{ 
	public:
		vectr(double x, double y, double z);
		vectr();
		double x, y, z;
		double dot(const vectr &a) const;
		double norm();
		double distance(vectr b);		
		vectr cross(const vectr &b) const;
		vectr VAdd(vectr a);
		vectr Vscalar(double b);
		void wrap(double boundary[6]);
		void collision(vectr x, vectr y);
		//vectr operator+=(const vectr &b);
		vectr operator*(double f) const;
		vectr operator/(double f) const;
		vectr operator-(const vectr &b) const;
		vectr operator+(const vectr &b) const;
}; //three dimensional vector

vectr RandVectr(double lowx, double upx, 
	double lowy, double upy, double lowz, double upz);
	
	

#endif
