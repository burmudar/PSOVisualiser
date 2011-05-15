#include "PSOStructures.h"

using namespace std;

Particle::Particle()
{
	pbest.fitness = -1.00;
	curFitness = 0;
	velocity = Vector3d();
	setPosition(Vector3d());
}

Particle::Particle(const Vector3d &pos,const int cuid)
{
	pbest.fitness = -1.00;
	pbest.uid = cuid;
	uid = cuid;
	curFitness = 0;
	velocity = Vector3d();
	setPosition(pos);
}

Particle::~Particle()
{
}

void Particle::setPosition(const double x,const double y, const double z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Particle::setPosition(const Vector3d& npos)
{
	position.x = npos.x;
	position.y = npos.y;
	position.z = npos.z;
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

double& Particle::getCurrentFitness()
{
	return curFitness;
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
	outstr << "pbest.pos: " << pbest.pos << endl << " pbest.fitness: " << pbest.fitness;
	outstr << " Current Position:"<<position<<endl;
	outstr << " Current Velocity: "<<velocity<<endl;
	return outstr.str(); 
}

/*
	pbest.fitness is initialized to -1 in the contructor, so we just check for the base case
	when we don't have a base fitness yet as well (Particle was just initialized}
*/
void Particle::setFitness(double &fitness)
{
	curFitness = fitness;
	if (curFitness < pbest.fitness || pbest.fitness == -1) 
	{
		pbest.fitness = fitness;
		pbest.pos = position;
	}
}
// Definition of gfxParticle starts
gfxParticle::gfxParticle():Particle()
{
	selected = false;
	size = 0.005;
}

gfxParticle::gfxParticle(const Vector3d &pos,const int uid):Particle(pos,uid)
{
	selected = false;	
	size = 0.005;
}

void gfxParticle::drawPoint(const Vector3d& pos)
{
	GLfloat size[2];
	glGetFloatv(GL_POINT_SIZE_RANGE,size);

	glPointSize(size[0]+5);
	glBegin(GL_POINTS);
		glVertex3f(pos.x,pos.y,pos.z);
	glEnd();
}

void gfxParticle::drawCube(const Vector3d& pos)
{
	glBegin(GL_QUADS);
		//front face
		glVertex3f(pos.x-size,pos.y+size,pos.z+size);
		glVertex3f(pos.x+size,pos.y+size,pos.z+size);
		glVertex3f(pos.x+size,pos.y-size,pos.z+size);
		glVertex3f(pos.x-size,pos.y-size,pos.z+size);
		//backface
		glVertex3f(pos.x-size,pos.y+size,pos.z-size);
		glVertex3f(pos.x+size,pos.y+size,pos.z-size);
		glVertex3f(pos.x+size,pos.y-size,pos.z-size);
		glVertex3f(pos.x-size,pos.y-size,pos.z-size);
		//right face
		glVertex3f(pos.x+size,pos.y+size,pos.z-size);
		glVertex3f(pos.x+size,pos.y+size,pos.z+size);
		glVertex3f(pos.x+size,pos.y-size,pos.z+size);
		glVertex3f(pos.x+size,pos.y-size,pos.z-size);
		//Left face	
		glVertex3f(pos.x-size,pos.y+size,pos.z-size);
		glVertex3f(pos.x-size,pos.y+size,pos.z+size);
		glVertex3f(pos.x-size,pos.y-size,pos.z+size);
		glVertex3f(pos.x-size,pos.y-size,pos.z-size);
		//Top face	
		glVertex3f(pos.x-size,pos.y+size,pos.z-size);
		glVertex3f(pos.x+size,pos.y+size,pos.z-size);
		glVertex3f(pos.x+size,pos.y+size,pos.z+size);
		glVertex3f(pos.x-size,pos.y+size,pos.z+size);
		//Bottom face	
		glVertex3f(pos.x-size,pos.y-size,pos.z-size);
		glVertex3f(pos.x+size,pos.y-size,pos.z-size);
		glVertex3f(pos.x+size,pos.y-size,pos.z+size);
		glVertex3f(pos.x-size,pos.y-size,pos.z+size);
	glEnd();
}

gfxParticle::~gfxParticle(){}

void gfxParticle::draw(int mode,int shape)
{
	if (mode == GL_SELECT)
	{
		glLoadName(uid);
	}
	if (selected)
	{
		glColor3f(1.0,0.0,0.0);
	}
	else
	{
		Vector3d colorVec(position.x,position.y,position.z);
		colorVec.normalize();
		//glColor3f(0.5 - position.z/pbest.fitness,0.5 - position.y/pbest.fitness,0.5 - position.x/pbest.fitness);
		glColor3f((colorVec.x + 1)/2,(colorVec.y+1)/2,(colorVec.z+1)/2);
		//glColor3f(0.5*position.x/pbest.fitness,0.5*position.y/pbest.fitness,0.5*position.z/pbest.fitness);
	}
	switch(shape)
	{
		case 1:
			drawPoint(position);
		break;
		case 2:
			drawCube(position);
		break;
	}
}

void gfxParticle::drawBest(int mode,int shape)
{
	if (mode == GL_SELECT)
	{
		glLoadName(uid);
	}
	if (selected)
	{
		glColor3f(1.0,0.0,0.0);
	}
	else
	{
		Vector3d colorVec(pbest.fitness,pbest.fitness,pbest.fitness);
		colorVec.normalize();
		glColor3f(1.0 - (colorVec.x + 1) / 2,1.0 - (colorVec.y+1)/2,1.0 - (colorVec.z+1)/2);
	}
	switch(shape)
	{
		case 1:
			drawPoint(pbest.pos);
		break;
		case 2:
			drawCube(pbest.pos);
		break;
	}
}

void gfxParticle::drawGraphPoint()
{
	//We assume that we are in a GL_QUAD block
	glColor3f(pbest.pos.x,pbest.pos.y,pbest.pos.z);
	glVertex3f(pbest.pos.y,pbest.fitness,pbest.pos.x);
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
//							PSO Class DEFINITIONS
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
BasePSO::BasePSO()
{
	population = 0;
	c1 = 0.41;
	c2 = 0.52;
	swarm = vector<gfxParticle>(population);
	initializeSwarm();
	BenchmarkFunctionFactory *functionFactory = new BenchmarkFunctionFactory();
	function = functionFactory->createDeJongF1();
	delete functionFactory;
}

BasePSO::~BasePSO()
{
	delete function;
}

BasePSO::BasePSO(const int &pop,Benchmark* benchFunction,const double &c1,const double &c2)
{
	this->population = pop;
	this->c1 = c1;
	this->c2 = c2;
	this->swarm = vector<gfxParticle>(population);
	this->function = benchFunction;

}
void BasePSO::setFunction(Benchmark* func)
{	
	function = func;
}

void BasePSO::nextFunction()
{
	BenchmarkFunctionFactory *functionFactory = new BenchmarkFunctionFactory();
	Benchmark *function = functionFactory->createNextFunction(this->function->getBenchmarkFunctionType());
	delete functionFactory;
	setFunction(function);
	initialize();
}

Benchmark* BasePSO::getFunction()
{
	return function;
}

string BasePSO::getFunctionName() const
{
	return function->name();
}

int BasePSO::getSwarmSize()
{
	return population;
}

gfxParticle* BasePSO::getParticle(const int& index)
{
	return &swarm[index];
}

void BasePSO::initialize()
{
	initializeSwarm();
	evaluateParticle(0);
	global_best = swarm[0].getParticleBest();
}

void BasePSO::evaluateSwarm()
{
	for(unsigned int i =0; i < swarm.size();i++)
	{
		evaluateParticle(i);
	}
}

void BasePSO::evaluateParticle(const int& index)
{
	double answ;
	answ = function->evaluate(swarm[index].getPosition());
	swarm[index].setFitness(answ);
	if(swarm[index].getBestFitness() < global_best.fitness)
	{
		global_best = swarm[index].getParticleBest();
	}
}

void BasePSO::updateSwarmMovement()
{
	boost::mt19937 rng(time(0));
	boost::uniform_real<double> u(0.00,1.00);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen(rng, u);	
	for(unsigned int i =0; i < swarm.size();i++)
	{
		swarm[i].velocity = swarm[i].velocity + c1 * gen() * (swarm[i].getBestPosition() - swarm[i].getPosition()) + c2 * gen() * (global_best.pos - swarm[i].getPosition());
		swarm[i].move();
		evaluateParticle(i);
	}
}

bool BasePSO::isSwarmBestAtOptimum()
{
	bool result = this->function->isOptimum(global_best.fitness);
	return result;
}

void BasePSO::initializeSwarm()
{
	BenchmarkPositionGenerator *generator = function->createPositionGenerator();
	for(int i =0; i < population; i++)
	{
		Vector3d position = generator->generatePosition();
		swarm[i] = gfxParticle(position,i);
	}
	delete generator;
}

InertiaPSO::InertiaPSO(const int& pop,Benchmark* func, const double& c1,const double& c2, const double& inertia) : BasePSO(pop,func,c1,c2)
{
	this->inertia = inertia;
}

InertiaPSO::~InertiaPSO()
{
}

void InertiaPSO::updateSwarmMovement()
{
	boost::mt19937 rng(time(0));
	boost::uniform_real<double> u(0.00,1.00);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen(rng, u);	
	for(unsigned int i =0; i < swarm.size();i++)
	{
		swarm[i].velocity = (inertia * swarm[i].velocity) + c1 * gen() * (swarm[i].getBestPosition() - swarm[i].getPosition()) + c2 * gen() * (global_best.pos - swarm[i].getPosition());
		swarm[i].move();
		evaluateParticle(i);
	}
}

ConstrictionPSO::ConstrictionPSO(const int& pop, Benchmark* func, const double& c1,const double& c2, const double& constriction):BasePSO(pop,func,c1,c2)
{
	this->constriction = constriction;
}

double ConstrictionPSO::calculateConstrictionCoefficient(const double& r1, const double& r2)
{
	double alpha = c1*r1 + c2*r2;
	return (2 * constriction) / abs(2 - alpha - sqrt(alpha * (alpha - 4)));
}

void ConstrictionPSO::updateSwarmMovement()
{	
	boost::mt19937 rng(time(0));
	boost::uniform_real<double> u(0.00,1.00);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen(rng, u);	
	
	double c_coefficient,r1,r2;
	for(unsigned int i =0; i < swarm.size();i++)
	{
		r1 = gen();
		r2 = gen();
		c_coefficient = calculateConstrictionCoefficient(r1,r2);
		if(c_coefficient < 4)
		{
			swarm[i].velocity = (swarm[i].velocity + c1 * r1 * (swarm[i].getBestPosition() - swarm[i].getPosition()) + c2 * r2 * (global_best.pos - swarm[i].getPosition()));
		}
		else
		{
			swarm[i].velocity = c_coefficient * (swarm[i].velocity + c1 * r1 * (swarm[i].getBestPosition() - swarm[i].getPosition()) + c2 * r2 * (global_best.pos - swarm[i].getPosition()));
		}
		swarm[i].move();
		evaluateParticle(i);
	}
}

GraphicalPSOVisualizer::GraphicalPSOVisualizer(BasePSO* pso)
{
	draw_normal = true;
	draw_best = true;
	selectedParticleUID = 0;
	this->pso = pso;
	this->pso->initialize();
}

GraphicalPSOVisualizer::~GraphicalPSOVisualizer()
{
	delete pso;
}

void GraphicalPSOVisualizer::setFunction(Benchmark *func)
{
	draw_normal = true;
	draw_best = true;
	selectedParticleUID = 0;
	pso->setFunction(func);
}

void GraphicalPSOVisualizer::nextFunction()
{
	pso->nextFunction();
}

Benchmark* GraphicalPSOVisualizer::getFunction()
{
	return pso->getFunction();
}

std::string GraphicalPSOVisualizer::getFunctionName() const
{
	return pso->getFunctionName();
}

void GraphicalPSOVisualizer::updateSwarmMovement()
{
	pso->updateSwarmMovement();
}

bool GraphicalPSOVisualizer::isSwarmBestAtOptimum()
{
	return pso->isSwarmBestAtOptimum();
}

ParticleBest GraphicalPSOVisualizer::getPSOGlobalBest()
{
	return pso->global_best;
}

const gfxParticle& GraphicalPSOVisualizer::getSelectedParticle()
{
	if(selectedParticleUID < 0)
		return (*pso->getParticle(0));
	return (*pso->getParticle(selectedParticleUID));
}

void GraphicalPSOVisualizer::selectParticle(const int &uid)
{
	pso->getParticle(selectedParticleUID)->selected = false;
	selectedParticleUID = uid;
	pso->getParticle(selectedParticleUID)->selected = true;
}

const SceneConfig GraphicalPSOVisualizer::getFunctionSceneConfig()
{
	return pso->getFunction()->getSceneConfigForBenchmark();
}

void GraphicalPSOVisualizer::draw(const int renderMode,const int drawShape)
{
	int swarm_size = pso->getSwarmSize();
	if (drawShape == 3)
	{
		glBegin(GL_QUADS);
		for (int i =0; i < swarm_size;i++)
		{
			gfxParticle& particle = (*pso->getParticle(i));
			if (particle.getBestFitness() < 50 && (particle.getBestPosition().x <= 4 || particle.getBestPosition().x >= -4) && (particle.getBestPosition().y <= 4 || particle.getBestPosition().y >= -4));
				particle.drawGraphPoint();
		}
		glEnd();
	}
	for (int i =0; i < swarm_size;i++)
	{
		gfxParticle& particle = (*pso->getParticle(i));
		if (draw_normal)
			particle.draw(renderMode,drawShape);
		if (draw_best)
			particle.drawBest(renderMode,drawShape);
	}
}

PSOFactory::PSOFactory(const double& c1,const double& c2,const int& population)
{
	this->c1 = c1;
	this->c2 = c2;
	this->population = population;
}

void PSOFactory::setC1(const double& c1)
{
	this->c1 = c1;
}

void PSOFactory::setC2(const double& c2)
{
	this->c2 = c2;
}

void PSOFactory::setPopulation(const int& population)
{
	this->population = population;
}

BasePSO* PSOFactory::createNormalPSO(Benchmark* function)
{
	return new BasePSO(population,function,c1,c2);
}

BasePSO* PSOFactory::createInertiaPSO(const double& inertia,Benchmark* function)
{
	return new InertiaPSO(population,function,c1,c2,inertia);
}

BasePSO* PSOFactory::createConstrictionPSO(const double& constriction,Benchmark* function)
{
	return new ConstrictionPSO(population,function,c1,c2,constriction);
}

void PSOPerformanceStats::measure(BasePSO* pso)
{
	cout << "Accuracy: " << accuracy(pso) << " | ";
	cout << "Diversity:" << diversity(pso) ;
}

const double PSOPerformanceStats::accuracy(BasePSO* pso)
{
	Benchmark* function = pso->getFunction();
	return abs(pso->global_best.fitness - function->getOptimalFitness());
}

Vector3d* PSOPerformanceStats::calculateSwarmAvg(BasePSO* pso)
{
	Vector3d* avg = new Vector3d();
	for(int i = 0; i < pso->getSwarmSize(); i++)
	{
		Vector3d particle_pos = pso->getParticle(i)->getPosition();
		avg->x += particle_pos.x; 
		avg->y += particle_pos.y;
		avg->z += particle_pos.z;
	}
	avg->x = avg->x / pso->getSwarmSize();
	avg->y = avg->y / pso->getSwarmSize();
	avg->z = avg->z / pso->getSwarmSize();
	return avg;
}

const double PSOPerformanceStats::diversity(BasePSO* pso)
{
	double diversity = 0;
	int swarm_size = pso->getSwarmSize();
	Vector3d* swarm_avg = calculateSwarmAvg(pso);
	int dimension = pso->getFunction()->dimensionality();
	for(int i = 0; i < swarm_size; i++)
	{
		Vector3d& pos = pso->getParticle(i)->getPosition();
		double diff_squared = 0;
		if(dimension == 2)
		{
			 diff_squared = (pow(pos.x - swarm_avg->x,2) + pow(pos.y - swarm_avg->y,2));
		}
		else
		{
			 diff_squared = (pow(pos.x - swarm_avg->x,2) + pow(pos.y - swarm_avg->y,2) + pow(pos.z - swarm_avg->z,2));
		}
		diversity += sqrt(diff_squared);
	}
	delete	swarm_avg;
	return diversity / swarm_size;
}

