#include "gfxmath.h"
#include "PSOStructures.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

void initRandomParticle(vector<Particle>& swarm,const int& population)
{
	boost::mt19937 rng;
	boost::uniform_real<double> u(-5.14,5.14);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen(rng, u);
	for(int i =0; i < population;i++)
	{
		double x = gen();
		double y = gen();
		double z = gen();
		swarm[i] = Particle(Vector3d(x,y,z));
	}
}

void evaluateSwarm(vector<Particle>& swarm,ParticleBest& cgbest)
{
	for(int i = 0;i < swarm.size();i++)
	{
		if(swarm[i].getBestFitness() < cgbest.fitness)
		{
			cgbest = swarm[i].getParticleBest();
		}
	}
}

void printSwarmReport(const vector<Particle>& pswarm,const ParticleBest& gbest)
{
	cout << "Swarm Report" << endl;
	cout << "************" << endl;
	cout << "Swarm Best Position: " << gbest.pos << endl;
	cout << "Swarm Best Fitness: " << gbest.fitness << endl;
	for (int i = 0; i < pswarm.size();i++)
	{
		cout << pswarm[i].info()<<endl;
	}
}

void runPSO(const int& population,const int maxIter)
{
	cout << "Starting Particle Swarm Optimization with " << population << " population" << endl;
	cout << "Max Iterations set to : " << maxIter << endl;
	vector<Particle> pswarm(population); 
	initRandomParticle(pswarm,population);
	ParticleBest gbest = pswarm[0].getParticleBest();
	evaluateSwarm(pswarm,gbest);
	double c1 = 0.41;
	double c2 = 0.52;
	boost::mt19937 rng;
	boost::uniform_real<double> u(0.00,1.00);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen(rng, u);
	for (int i =0; i < maxIter; i++)
	{
			for(int i =0; i < population;i++)
			{
				pswarm[i].velocity = pswarm[i].velocity + c1 * gen() * (pswarm[i].getBestPosition() - pswarm[i].getPosition()) + c2 * (gbest.pos - pswarm[i].getPosition());
				pswarm[i].move();
			}
		evaluateSwarm(pswarm,gbest);
	}
	printSwarmReport(pswarm,gbest);
}

int main(int argc,char* argv[])
{
	if (argc < 3)
	{
		cout << "pso population iterations" << endl;
		return 0;
	}
	else
	{
		istringstream pop(argv[1]);
		istringstream iter(argv[2]);
		int ipop,iiter;
		pop >> ipop;
		iter >> iiter;
		runPSO(ipop,iiter);
	}
	return 0;
}
