#include "PSOStructures.h"

using namespace std;

Particle::Particle()
{
	pbest.fitness = -1.00;
	setPosition(Vector3d());
	velocity = Vector3d();
}

Particle::Particle(const Vector3d &pos,const int cuid)
{
	pbest.fitness = -1.00;
	setPosition(pos);
	velocity = Vector3d();
	uid = cuid;
}

Particle::~Particle()
{
}

void Particle::setPosition(const double x,const double y, const double z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	evaluate();
}

void Particle::setPosition(const Vector3d& npos)
{
	position.x = npos.x;
	position.y = npos.y;
	position.z = npos.z;
	evaluate();
}

Vector3d& Particle::getPosition() 
{
	return position;
}

Vector3d& Particle::getBestPosition() 
{
	return pbest.pos;
}

double& Particle::getBestFitness() 
{
	return pbest.fitness;
}

ParticleBest& Particle::getParticleBest() 
{
	return pbest;
}

int& Particle::getUID()
{
	return uid;
}

void Particle::move()
{
	setPosition(position + velocity);
}

const string Particle::info() 
{
	ostringstream outstr;
	outstr << "pbest.pos: " << pbest.pos << endl << "pbest.fitness: " << pbest.fitness<<endl;
	outstr << "Current Position:"<<position<<endl;
	outstr << "Current Velocity: "<<velocity<<endl;
	return outstr.str(); 
}

//evaluate gets called in the constructor and both the setPositions because we need to 
//evaluate our position each time it changes to determine how good our fitness is.
const double Particle::evaluate()
{
	//De Jong F1 Function: x^2 + y^2 + z^2 + ...
	double answ = pow(position.x,2) + pow(position.y,2) + pow(position.z,2);
	if (pbest.fitness < EPSILON)
	{
		pbest.fitness = answ;
		pbest.pos = position;
	}
	else if (answ < pbest.fitness) 
	{
		pbest.fitness = answ;
		pbest.pos = position;
	}
	return answ;
}
