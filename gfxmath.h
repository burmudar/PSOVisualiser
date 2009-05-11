#ifndef GFXMATH_H
#define GFXMATH_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>

class Vector3d
{
public:
	double x,y,z,w;

	Vector3d();
	Vector3d(const Vector3d& a);
	Vector3d(const double& x,const double& y,const double& z);
	Vector3d(const double& x,const double& y,const double& z,const double& w);
	~Vector3d();
	//Operators
	bool operator==(const Vector3d& b) const;
	Vector3d operator+(const Vector3d& right)const;
	Vector3d operator-(const Vector3d& right)const;
	Vector3d operator+() const;
	Vector3d operator-() const;
	Vector3d& operator=(const Vector3d& right);
	//dot product
	friend const double operator* (const Vector3d& left,const Vector3d& right);
	friend Vector3d operator* (const Vector3d& left,double right);
	friend Vector3d operator* (double left,const Vector3d& right);
	Vector3d operator% (const Vector3d& right)const;
	friend Vector3d operator / (const Vector3d& left,double right);
	Vector3d operator^ (const Vector3d& right)const;
	friend std::ostream& operator<< (std::ostream& out,const Vector3d& b);
	double norm();
	void normalize();
	Vector3d reflect(const Vector3d& v, const Vector3d& n);
	Vector3d transmit(Vector3d i, Vector3d n, double n1,double n2);
	std::string toString();
};
typedef class Vector3d Vector3d;
#endif
