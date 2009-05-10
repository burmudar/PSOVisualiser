#ifndef PSOSTRUCTURES_H
#define PSOSTRUCTURES_H

#include "gfxmath.h"
#include "DeJongFunctions.h"
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <boost/random.hpp>
#include <GL/glu.h>
#include <GL/gl.h>

const double EPSILON = 0.00000000001;
struct ParticleBest
{
		Vector3d pos;
		double fitness;  
		int uid;
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
	void setFitness(double &fitness);
	Vector3d& getPosition();
	Vector3d& getBestPosition() ;
	double& getBestFitness() ;
	double& getCurrentFitness();
	ParticleBest& getParticleBest() ;
	int& getUID();
	void move();
	const std::string info() ;
protected:
	ParticleBest pbest;
	Vector3d position;
	double curFitness;
	int uid;
};

class gfxParticle : public Particle
{
	public:
		bool selected;
		float size;
		gfxParticle();
		gfxParticle(const Vector3d &pos,const int uid);
		~gfxParticle();
		void draw(int mode,int shape);
		void drawBest(int mode,int shape);
	private:
		void drawCube(const Vector3d& pos);
		void drawPoint(const Vector3d& pos);
};

class ConsolePSO 
{
public:
	ConsolePSO();
	ConsolePSO(const int &pop,const int &func,const double &c1,const double &c2);
	~ConsolePSO();
	void evaluateSwarm();
	void evaluateParticle(const int &index);
	void updateSwarmMovement();
	void print();
	ParticleBest global_best;
protected:
	void initializeSwarm(int func);
private:
	std::vector<Particle> swarm;
	int population;
	double c1,c2;
	DeJong * function;
};

class GraphicalPSO 
{
public:
	GraphicalPSO();
	GraphicalPSO(const int &pop,const int &func,const double &c1,const double &c2);
	~GraphicalPSO();
	void evaluateSwarm();
	void evaluateParticle(const int &index);
	void updateSwarmMovement();
	const gfxParticle& getSelectedParticle();
	void selectParticle(const int &uid);
	void draw(int renderMode,int drawShape);
	bool draw_normal;
	bool draw_best;
	ParticleBest global_best;
protected:
	void initializeSwarm(const int &func);
private:
	std::vector<gfxParticle> swarm;
	int selectedParticleUID;
	int population;
	double c1,c2;
	DeJong * function;
};

typedef class Particle Particle;
typedef class gfxParticle gfxParticle;
typedef struct ParticleBest ParticleBest;
typedef class GraphicalPSO GraphicalPSO;
typedef class ConsolePSO ConsolePSO;
#endif
