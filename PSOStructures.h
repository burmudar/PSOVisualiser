#ifndef PSOSTRUCTURES_H
#define PPSOSTRUCTURES_H

#include "gfxmath.h"
#include <string>
#include <sstream>
#include <cmath>
#include <boost/random.hpp>
const double EPSILON = 0.00000000001;
struct ParticleBest
{
		Vector3d pos;
		double fitness;  
};
class Particle
{
public:
	Vector3d velocity;
	Particle();//evalute gets called at the end of this constructor
	Particle(const Vector3d &pos,const int i);//evalute gets called at the end of this constructor
	~Particle();
	void setPosition(const double x,const double y,const double z);//evaluate gets called at the end in this function
	void setPosition(const Vector3d& npos);//evaluate gets called at the end in this function
	Vector3d& getPosition() ;
	Vector3d& getBestPosition() ;
	double& getBestFitness() ;
	ParticleBest& getParticleBest() ;
	int& getUID();
	void move();
	const std::string info() ;
	const double evaluate();
private:
	ParticleBest pbest;
	Vector3d position;
	int uid;
};
typedef class Particle Particle;
typedef struct ParticleBest ParticleBest;
#endif
