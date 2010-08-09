#ifndef PSOSTRUCTURES_H
#define PSOSTRUCTURES_H

#include "BenchFunctions.h"
#include "gfxstructures.h"
#include "boost/random.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
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
		void drawGraphPoint();
	private:
		void drawCube(const Vector3d& pos);
		void drawPoint(const Vector3d& pos);
};

class ConsolePSO 
{
public:
	ConsolePSO();
	ConsolePSO(const int &pop,Benchmark* func,const double &c1,const double &c2,const double& inertia);
	~ConsolePSO();
	void setFunction(Benchmark* func);
	void nextFunction();
	void evaluateSwarm();
	void evaluateParticle(const int &index);
	void updateSwarmMovement();
	void print();
	ParticleBest global_best;
protected:
	void initializeSwarm();
private:
	std::vector<Particle> swarm;
	int population;
	double c1,c2,inertia;
	Benchmark *function;
};

class GraphicalPSO 
{
public:
	GraphicalPSO();
	GraphicalPSO(const int &pop,Benchmark* func,const double &c1,const double &c2);
	~GraphicalPSO();
	void initialize();
	void setFunction(Benchmark* func);
	void nextFunction();
	void evaluateSwarm();
	void evaluateParticle(const int &index);
	virtual void updateSwarmMovement();
	std::string functionName() const;
	const gfxParticle& getSelectedParticle();
	void selectParticle(const int &uid);
	const SceneConfig getFunctionSceneConfig();
	void draw(int renderMode,int drawShape);
	bool draw_normal;
	bool draw_best;
	ParticleBest global_best;
protected:
	void initializeSwarm();
	std::vector<gfxParticle> swarm;
	int selectedParticleUID;
	int population;
	double c1,c2;
	Benchmark *function;
};

class GraphicalInertiaPSO : public GraphicalPSO
{
public:
	GraphicalInertiaPSO(const int &pop,Benchmark* func,const double &c1,const double &c2,const double& inertia);
	virtual void updateSwarmMovement();
private:
	double inertia;
};

class GraphicalConstrictionPSO : public GraphicalPSO
{
public:
	GraphicalConstrictionPSO(const int &pop,Benchmark* func,const double &c1,const double &c2,const double& constriction);
	virtual void updateSwarmMovement();
private:
	double calculateConstrictionCoefficient();
	double constriction;
};

typedef class Particle Particle;
typedef class gfxParticle gfxParticle;
typedef struct ParticleBest ParticleBest;
typedef class GraphicalPSO GraphicalPSO;
typedef class GraphicalInertiaPSO GraphicalInertiaPSO;
typedef class GraphicalConstrictionPSO GraphicalConstrictionPSO;
typedef class ConsolePSO ConsolePSO;
#endif
