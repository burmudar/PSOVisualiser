#define EPS 0.00000000001;
#include "gfxmath.h"

using namespace std;

//Vector
Vector3d::Vector3d()
{
	this->x=EPS;this->y=EPS;this->z=EPS;this->w=EPS;
}

//Copy constructor
Vector3d::Vector3d(const Vector3d& a)
{
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->w = a.w;
}

Vector3d::Vector3d(const double& x,const double& y,const double& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = EPS;
}

Vector3d::Vector3d(const double& x,const double& y,const double& z,const double& w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector3d::~Vector3d()
{
}

bool Vector3d::operator==(const Vector3d& b) const 
{
	return ((x==b.x)&&(y==b.y)&&(z==b.z)&&(w==b.w));
}

Vector3d Vector3d::operator+(const Vector3d& right) const
{
	
	return Vector3d(x+right.x,y+right.y,z+right.z,w);;
}

Vector3d Vector3d::operator- (const Vector3d& right) const
{
	return Vector3d(this->x-right.x,this->y-right.y,this->z-right.z,this->w);
}

Vector3d Vector3d::operator+() const
{
	return *this;
}

Vector3d Vector3d::operator-() const
{
	return Vector3d(*this * -1);
}

Vector3d& Vector3d::operator=(const Vector3d& right)
{
	if (this ==&right) return *this;
	x = right.x;
	y = right.y;
	z = right.z;
	w = right.w;
	return *this;
}

const double operator* (const Vector3d& left,const Vector3d& right)
{
	return left.x*right.x+left.y*right.y+left.z*right.z;
}

Vector3d operator* (const double left, const Vector3d& right)
{
	return Vector3d(left*right.x,left*right.y,left*right.z);
}

Vector3d operator* (const Vector3d& left, const double right)
{
	return Vector3d(left.x*right,left.y*right,left.z*right);
}

Vector3d Vector3d:: operator% (const Vector3d& right) const
{
	return Vector3d(x*right.x,y*right.y,z*right.z);
}

Vector3d operator/ (const Vector3d& left, const double right) 
{
	return Vector3d(left.x/right,left.y/right,left.z/right);
}
//Cross Product
Vector3d  Vector3d::operator^ (const Vector3d& right) const
{
	Vector3d returnValue = Vector3d();
	returnValue.x = y*right.z - z*right.y;
	returnValue.y = z*right.x - x*right.z;
	returnValue.z = x*right.y - y*right.x;
	returnValue.w = w;
	return returnValue;
}

ostream& operator<< (ostream& out,const Vector3d& b)
{
	return out << "{" << b.x << "," << b.y << "," << b.z << "," << b.w << "}";
}

double Vector3d::norm()
{
	return sqrt(x*x+y*y+z*z);
}

void Vector3d::normalize()
{
	double s = norm();
	if(s != 0.0)
	{
		x = x / s;
		y = y / s;
		z = z / s;
	}
}

Vector3d Vector3d::reflect(const Vector3d& v, const Vector3d& n)
{
	Vector3d r = 2.0*(v*n)*n-v;
	return r;
}

Vector3d Vector3d::transmit(Vector3d i,Vector3d n, double n1,double n2)
{
	Vector3d t;
	double w,r,k;
	if (n*i>0.0)
	{
		n = -n;
		r = n1;
		n1 = n2;
		n2 = r;
	}
	r = n1 / n2;
	w = -i*n*r;
	k = 1.0+(w-r)*(w*r);
	//check for total internal reflection
	if(k<0.0) return reflect(-i,n);
	k = sqrt(k);
	t = r*i+(w-k)*n;
	t.normalize();
	return t;
}

string Vector3d::toString()
{
	ostringstream outstr;
	outstr << "(" << x << "," << y << "," << z << "," << w << ")";
	return outstr.str();
}
