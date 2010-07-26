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
		glColor3f(0.5 - position.z/pbest.fitness,0.5 - position.y/pbest.fitness,0.5 - position.x/pbest.fitness);
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
		glColor3f(1.0,1.0,1.0);
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

ConsolePSO::ConsolePSO()
{
	population = 0;
	c1 = 0.41;
	c2 = 0.52;
	inertia = 0.5;
	swarm = vector<Particle>(population);
	initializeSwarm();
	BenchmarkFunctionFactory *functionFactory = new BenchmarkFunctionFactory();
	function = functionFactory->createDeJongF1();
	delete functionFactory;
	evaluateSwarm();
	global_best = swarm[0].getParticleBest();
}

ConsolePSO::ConsolePSO(const int &pop,Benchmark* func,const double &c1,const double &c2,const double& inertia)
{
	population = pop;
	this->c1 = c1;
	this->c2 = c2;
	this->inertia = inertia;
	swarm = vector<Particle>(population);
	initializeSwarm();
	function = func;
	evaluateSwarm();
	global_best = swarm[0].getParticleBest();
}

ConsolePSO::~ConsolePSO()
{
	delete function;
}

void ConsolePSO::setFunction(Benchmark *func)
{
	function = func;
	initializeSwarm();
	evaluateSwarm();
	global_best = swarm[0].getParticleBest();
}

void ConsolePSO::nextFunction()
{
	BenchmarkFunctionFactory *functionFactory = new BenchmarkFunctionFactory();
	Benchmark *function = functionFactory->createNextFunction(this->function->getBenchmarkFunctionType());
	delete functionFactory;
	setFunction(function);
}

void ConsolePSO::initializeSwarm()
{
	BenchmarkPositionGenerator *generator = function->createPositionGenerator();
	for(int i = 0; i < population; i++)
	{
		swarm[i] = Particle(generator->generatePosition(),i);
	}
	delete generator;
}

void ConsolePSO::evaluateSwarm()
{
	for(int i = 0;i < population;i++)
	{
		evaluateParticle(i);
	}
}

/*
   Evaluate the particle at given index with the current set DeJong Function. Also check
   if the evaluated particle fitness is beter than the global best fitness
*/
void ConsolePSO::evaluateParticle(const int &index)
{
	double answ;
	answ = function->evaluate(swarm[index].getPosition());
	swarm[index].setFitness(answ);
	if(swarm[index].getBestFitness() < global_best.fitness || global_best.uid == -1)
	{
		global_best = swarm[index].getParticleBest();
	}
}

void ConsolePSO::updateSwarmMovement()
{
	boost::mt19937 rng(time(0));
	boost::uniform_real<double> u(0.00,1.00);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen(rng, u);	
	for(unsigned int i =0; i < swarm.size();i++)
	{
		swarm[i].velocity = (inertia * swarm[i].velocity) + c1 * gen() * (swarm[i].getBestPosition() - swarm[i].getPosition()) + c2 * (global_best.pos - swarm[i].getPosition());
		swarm[i].move();
		evaluateParticle(i);
	}
}

void ConsolePSO::print()
{
	for(int i = 0;i < population;i++)
	{
		std::cout << swarm[i].info() << endl;	
	}
}

GraphicalPSO::GraphicalPSO()
{
	population = 0;
	c1 = 0.41;
	c2 = 0.52;
	inertia = 0.5;
	swarm = vector<gfxParticle>(population);
	initializeSwarm();
	BenchmarkFunctionFactory *functionFactory = new BenchmarkFunctionFactory();
	function = functionFactory->createDeJongF1();
	delete functionFactory;
	draw_normal = true;
	draw_best = true;
	selectedParticleUID = 0;
	evaluateSwarm();
	global_best = swarm[0].getParticleBest();
}

GraphicalPSO::GraphicalPSO(const int &pop,Benchmark* benchFunction,const double &c1,const double &c2,const double& inertia)
{
	population = pop;
	this->c1 = c1;
	this->c2 = c2;
	this->inertia = inertia;
	swarm = vector<gfxParticle>(population);
	function = benchFunction;
	draw_normal = true;
	draw_best = true;
	selectedParticleUID = 0;

	initializeSwarm();
	evaluateSwarm();
	global_best = swarm[0].getParticleBest();
}

GraphicalPSO::~GraphicalPSO()
{
	delete function;
}

void GraphicalPSO::setFunction(Benchmark *func)
{
	function = func;
	initializeSwarm();
	draw_normal = true;
	draw_best = true;
	selectedParticleUID = 0;
	evaluateSwarm();
	global_best = swarm[0].getParticleBest();
}

void GraphicalPSO::nextFunction()
{
	BenchmarkFunctionFactory *functionFactory = new BenchmarkFunctionFactory();
	Benchmark *function = functionFactory->createNextFunction(this->function->getBenchmarkFunctionType());
	delete functionFactory;
	setFunction(function);
}

void GraphicalPSO::initializeSwarm()
{
	BenchmarkPositionGenerator *generator = function->createPositionGenerator();

	for(int i =0; i < population; i++)
	{
		Vector3d position = generator->generatePosition();
		swarm[i] = gfxParticle(position,i);
	}
	cout <<"Initialized Swarm" << endl;
	delete generator;
}

void GraphicalPSO::evaluateSwarm()
{
	for(int i = 0;i < population;i++)
	{
		evaluateParticle(i);	
	}
}

/*
   Evaluate the particle at given index with the current set DeJong Function. Also check
   if the evaluated particle fitness is beter than the global best fitness
*/
void GraphicalPSO::evaluateParticle(const int &index)
{
	double answ;
	answ = function->evaluate(swarm[index].getPosition());
	swarm[index].setFitness(answ);
	if(swarm[index].getBestFitness() < global_best.fitness)
	{
		global_best = swarm[index].getParticleBest();
	}
}

void GraphicalPSO::updateSwarmMovement()
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

string GraphicalPSO::functionName() const
{
	return function->name();
}

const gfxParticle& GraphicalPSO::getSelectedParticle()
{
	if(selectedParticleUID < 0)
		return swarm[0];
	return swarm[selectedParticleUID];
}

void GraphicalPSO::selectParticle(const int &uid)
{
	swarm[selectedParticleUID].selected = false;
	selectedParticleUID = uid;
	swarm[selectedParticleUID].selected = true;
}

const SceneConfig GraphicalPSO::getFunctionSceneConfig()
{
	return function->getSceneConfigForBenchmark();
}

void GraphicalPSO::draw(const int renderMode,const int drawShape)
{
	if (drawShape == 3)
	{
		glBegin(GL_QUADS);
		for (int i =0; i < population;i++)
		{
			if (swarm[i].getBestFitness() < 50 && (swarm[i].getBestPosition().x <= 4 || swarm[i].getBestPosition().x >= -4) && (swarm[i].getBestPosition().y <= 4 || swarm[i].getBestPosition().y >= -4));
				swarm[i].drawGraphPoint();
		}
		glEnd();
	}
	for (int i =0; i < population;i++)
	{
		if (draw_normal)
			swarm[i].draw(renderMode,drawShape);
		if (draw_best)
			swarm[i].drawBest(renderMode,drawShape);
	}
}
