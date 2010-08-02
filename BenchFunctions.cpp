#include "BenchFunctions.h"

using namespace std;

BenchmarkPositionGenerator::BenchmarkPositionGenerator(double min, double max)
{
	rng = new boost::mt19937(time(0));
	distribution = new boost::uniform_real<double>(min,max);
	generator = new boost::variate_generator<boost::mt19937&, boost::uniform_real<double> >(*rng,*distribution);
}

BenchmarkPositionGenerator::~BenchmarkPositionGenerator()
{
	delete rng;
	delete distribution;
	delete generator;
}

Position2DGenerator::Position2DGenerator(double min,double max):BenchmarkPositionGenerator(min,max){}

Vector3d Position2DGenerator::generatePosition()
{
	double x = (*generator)();
	double y = (*generator)();
	double z = (*generator)();
	return Vector3d(x,y,z);
}

Position3DGenerator::Position3DGenerator(double min,double max):BenchmarkPositionGenerator(min,max){}

Vector3d Position3DGenerator::generatePosition()
{
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen = *generator;
	return Vector3d(gen(),gen(),gen());
}

CamelPositionGenerator::CamelPositionGenerator(double min1,double max1,double min2,double max2):BenchmarkPositionGenerator(min1,max1)
{
	boost::mt19937 rng(time(0));
	boost::uniform_real<double> v(min2,max2);
	generator2 = new boost::variate_generator<boost::mt19937&, boost::uniform_real<double> >(rng,v);
}

Vector3d CamelPositionGenerator::generatePosition()
{
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > gen = *generator;
	return Vector3d(gen(),gen(),0);
}

CamelPositionGenerator::~CamelPositionGenerator()
{
	delete generator2;
}

DeJongF1::DeJongF1()
{
	info = "x^2 + y^2 + z^2 + ... + n^2 where n is the dimensions";
}

double DeJongF1::evaluate(const Vector3d& pos)
{
	return pow(pos.x,2) + pow(pos.y,2) + pow(pos.z,2);
}

const string DeJongF1::name()
{
	return "DeJong Function F1";
}

const BENCHMARK_FUNCTION DeJongF1::getBenchmarkFunctionType()
{
	return DEJONGF1;
}

const SceneConfig DeJongF1::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 0.05;
	config.distance = 40;
	config.nearZPlane = 0.1f;
	config.farZPlane = 100.0f;
	return config;
}

BenchmarkPositionGenerator *DeJongF1::createPositionGenerator()
{
	return new Position2DGenerator(-5.12,5.12);
}

DeJongF5::DeJongF5()
{
	info = "Shekel's Foxhole";
	int value = -32;
	for(unsigned int row = 0; row < 2; row++)
	{
		for(unsigned int col = 0; col < 25; col++)
		{
			switch(row)
			{
				case 0:
				{
					a[row][col] = value;
					value = value + 16;
					if (value == 48)
					{
						value = -32;
					}
				}
				break;
				case 1:
				{
					a[row][col] = value;
					if((((col+1)%5)==0)&&(col  != 0))
					{
						value = value + 16;
						if (value == 48) value = 32;
					}
				}
				break;
			}
		}
	}
}

const string DeJongF5::name()
{
	return "DeJong Function F5 Shekel's Foxhole";
}

const BENCHMARK_FUNCTION DeJongF5::getBenchmarkFunctionType()
{
	return DEJONGF5;
}

const SceneConfig DeJongF5::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 200;
	config.nearZPlane = 0.1f;
	config.farZPlane = 8000.0f;
	return config;
}

BenchmarkPositionGenerator *DeJongF5::createPositionGenerator()
{
	return new Position2DGenerator(-65.356,65.356);
}

double DeJongF5::evaluate(const Vector3d& pos)
{
	double sumi;
	double sumj=0;
	for(unsigned int j = 0; j < 25; j++)
	{
		sumi = 0;
		sumi += pow(pos.x - a[0][j],6);
		sumi += pow(pos.y - a[1][j],6);
		sumj += 1.0/(j + sumi);
	}
	return 1.0/(1.0/500 + sumj);
}

Rastrigin::Rastrigin()
{
	info = "x^2 + y^2 + z^2 + ... + n^2 where n is the dimensions";
}

double Rastrigin::evaluate(const Vector3d& pos)
{
	double answ=0;
	answ += pow(pos.x,2) + 10*cos(2*PI*pos.x)+10; 
	answ += pow(pos.y,2) + 10*cos(2*PI*pos.y)+10; 
	answ += pow(pos.z,2) + 10*cos(2*PI*pos.z)+10; 
	return answ;
}

const string Rastrigin::name()
{
	return "Rastrigin Function";
}

const BENCHMARK_FUNCTION Rastrigin::getBenchmarkFunctionType()
{
	return RASTRIGIN;
}

const SceneConfig Rastrigin::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 1;
	config.distance = 100;
	config.nearZPlane = 0.1f;
	config.farZPlane = 8000.0f;
	return config;
}

BenchmarkPositionGenerator *Rastrigin::createPositionGenerator()
{
	return new Position3DGenerator(-5.12,5.12);
}



Schwefel::Schwefel()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Schwefel::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ += (-1 * pos.x)*sin(sqrt(abs(pos.x)));
	answ += (-1 * pos.y)*sin(sqrt(abs(pos.y)));
	answ += (-1 * pos.z)*sin(sqrt(abs(pos.z)));
	return 418.9829 * 3 + answ;
}

const string Schwefel::name()
{
	return "Schwefel Function 7";
}

const BENCHMARK_FUNCTION Schwefel::getBenchmarkFunctionType()
{
	return SCHWEFEL;
}

const SceneConfig Schwefel::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 1;
	config.distance = 100;
	config.nearZPlane = 0.1f;
	config.farZPlane = 8000.0f;
	return config;
}

BenchmarkPositionGenerator *Schwefel::createPositionGenerator()
{
	return new Position3DGenerator(-500,500);
}

Griewank::Griewank()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Griewank::evaluate(const Vector3d& pos)
{
	double answ1 = 1/4000;
	answ1 += pow(pos.x,2);
	answ1 += pow(pos.y,2);
	answ1 += pow(pos.z,2);
	double answ2 = 0;	
	answ2 *= cos(pos.x / sqrt(1));
	answ2 *= cos(pos.y / sqrt(2));
	answ2 *= cos(pos.z / sqrt(3));
	return answ1-answ2+1;
}

const string Griewank::name()
{
	return "Griewank Function";
}

const BENCHMARK_FUNCTION Griewank::getBenchmarkFunctionType()
{
	return GRIEWANK;
}

const SceneConfig Griewank::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 0.05;
	config.distance = 40;
	config.nearZPlane = 0.1f;
	config.farZPlane = 100.0f;
	return config;
}

BenchmarkPositionGenerator *Griewank::createPositionGenerator()
{
	return new Position3DGenerator(-600,600);
}

Salomon::Salomon()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Salomon::evaluate(const Vector3d& pos)
{
	double answ1 = 0;
	answ1 += pow(pos.x,2);
	answ1 += pow(pos.y,2);
	answ1 += pow(pos.z,2);
	answ1 = -cos(2*PI*sqrt(answ1));
	double answ2 = 0;	
	answ2 += pow(pos.x,2)+1;
	answ2 += pow(pos.y,2)+1;
	answ2 += pow(pos.z,2)+1;
	answ2 = 0.1*sqrt(answ2);
	return answ1+answ2;
}

const string Salomon::name()
{
	return "Salomon Function";
} 

const BENCHMARK_FUNCTION Salomon::getBenchmarkFunctionType()
{
	return SALAMON;
}

const SceneConfig Salomon::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 1000;
	config.nearZPlane = 0.1f;
	config.farZPlane = 5000.0f;
	return config;
}

BenchmarkPositionGenerator *Salomon::createPositionGenerator()
{
	return new Position3DGenerator(-65356,65356);
}

const BENCHMARK_FUNCTION Ackley::getBenchmarkFunctionType()
{
	return ACKLEY;
}

const SceneConfig Ackley::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 1000;
	config.nearZPlane = 0.1f;
	config.farZPlane = 5000.0f;
	return config;
}

Ackley::Ackley()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Ackley::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ += exp(-0.2);
	answ *= sqrt(pow(pos.x,2)+pow(pos.y,2));
	answ += 3*(cos(2*pos.x)+ sin(2*pos.y));
	return answ;
}

const string Ackley::name()
{
	return "Ackley Function in 2D";
}

BenchmarkPositionGenerator *Ackley::createPositionGenerator()
{
	return new Position2DGenerator(-32.768,32.768);
}

Camel::Camel()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Camel::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ += (4 - 2.1*pow(pos.x,2)+pow(pos.x,4)/3)*pow(pos.x,2)+(pos.x*pos.y)+(-4 +4*pow(pos.y,2))*pow(pos.y,2);
	return answ;
}

const string Camel::name()
{
	return "Six-Camel Hump Back Function ";
}

const BENCHMARK_FUNCTION Camel::getBenchmarkFunctionType()
{
	return CAMEL;
}

const SceneConfig Camel::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 1000;
	config.nearZPlane = 0.1f;
	config.farZPlane = 5000.0f;
	return config;
}

BenchmarkPositionGenerator *Camel::createPositionGenerator()
{
	return new CamelPositionGenerator(-3,3,-2,2);
}

Shubert::Shubert()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Shubert::evaluate(const Vector3d& pos)
{
	double answ1 = 0;
	for (int i =1; i <=5;i++)
	{
		answ1+=i*cos((i+1)*pos.x + i);	
	}
	double answ2=0;
	for (int i =1; i <=5;i++)
	{
		answ2 += i*cos((i+1)*pos.y + i);
	}
	return answ1*answ2;
}

const string Shubert::name()
{
	return "Shubert Function ";
}

const BENCHMARK_FUNCTION Shubert::getBenchmarkFunctionType()
{
	return SHUBERT;
}

const SceneConfig Shubert::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 1000;
	config.nearZPlane = 0.1f;
	config.farZPlane = 5000.0f;
	return config;
}

BenchmarkPositionGenerator *Shubert::createPositionGenerator()
{
	return new Position2DGenerator(-5.12,5.12);
}

Himmelblau::Himmelblau()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Himmelblau::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ = pow((pow(pos.x,2) + pos.y - 11),2) + pow((pos.x + pow(pos.y,2) - 7),2);
	return answ;
} 
const string Himmelblau::name()
{
	return "Himmelblau Function ";
}

const BENCHMARK_FUNCTION Himmelblau::getBenchmarkFunctionType()
{
	return HIMMELBLAU;
}

const SceneConfig Himmelblau::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 1000;
	config.nearZPlane = 0.1f;
	config.farZPlane = 5000.0f;
	return config;
}

BenchmarkPositionGenerator *Himmelblau::createPositionGenerator()
{
	return new Position2DGenerator(-65357,65357);
}

Rosenbrock::Rosenbrock()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Rosenbrock::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ = 100 * pow((pos.y - pow(pos.x,2)),2) + pow((1 - pos.x),2);
	answ = 100 * pow((pos.z - pow(pos.y,2)),2) + pow((1 - pos.y),2);
	return answ;
}

const string Rosenbrock::name()
{
	return "Rosenbrock Function ";
}

const BENCHMARK_FUNCTION Rosenbrock::getBenchmarkFunctionType()
{
	return ROSENBROCK;
}

const SceneConfig Rosenbrock::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 0.05;
	config.distance = 15;
	config.nearZPlane = 0.1f;
	config.farZPlane = 100.0f;

	return config;
}

BenchmarkPositionGenerator *Rosenbrock::createPositionGenerator()
{
	return new Position2DGenerator(-2.048,2.048);
}

DropWave::DropWave()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double DropWave::evaluate(const Vector3d& pos)
{
	double answ,powsum;
	powsum = pow(pos.x,2) + pow(pos.y,2);
	answ = 1 + cos(12*sqrt(powsum));
	answ /= 0.5*powsum + 2;
	return answ;
}

const string DropWave::name()
{
	return "DropWave Function ";
}

const BENCHMARK_FUNCTION DropWave::getBenchmarkFunctionType()
{
	return DROPWAVE;
}

const SceneConfig DropWave::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 15;
	config.distance = 45;
	config.nearZPlane = 0.1f;
	config.farZPlane = 100.0f;
	return config;
}

BenchmarkPositionGenerator *DropWave::createPositionGenerator()
{
	return new Position2DGenerator(-5.12,5.12);
}

Easom::Easom()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Easom::evaluate(const Vector3d& pos)
{
	double answ;
	answ = -cos(pos.x)*cos(pos.y)*exp(-1*pow(pos.x - PI,2) - pow(pos.y - PI,2));
	return answ;
}

const string Easom::name()
{
	return "Easom Function ";
}

const BENCHMARK_FUNCTION Easom::getBenchmarkFunctionType()
{
	return EASOM;
}

const SceneConfig Easom::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 15;
	config.distance = 45;
	config.nearZPlane = 0.1f;
	config.farZPlane = 100.0f;
	return config;
}

BenchmarkPositionGenerator *Easom::createPositionGenerator()
{
	return new Position2DGenerator(-100,100);
}

Branins::Branins()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Branins::evaluate(const Vector3d& pos)
{
	double answ;
	answ = pow(pos.y - ((5.1/(4*pow(PI,2)))*pow(pos.x,2)) + (5/PI)*pos.x - 6,2) + 10*(1-(1/(8*PI)))*cos(pos.x) + 10;
	return answ;
}

const string Branins::name()
{
	return "Branins Function ";
}

const BENCHMARK_FUNCTION Branins::getBenchmarkFunctionType()
{
	return BRANINS;
}

const SceneConfig Branins::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 0.05;
	config.distance = 15;
	config.nearZPlane = 0.1f;
	config.farZPlane = 100.0f;
	return config;
}


BenchmarkPositionGenerator *Branins::createPositionGenerator()
{
	return new Position2DGenerator(-65535,65535);
}

Michalewicz::Michalewicz()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Michalewicz::evaluate(const Vector3d& pos)
{
	double answ,m;
	m = 20;
	answ = -sin(pos.x)*pow(sin(pow(pos.x,2)/PI),m) - sin(pos.y)*pow(sin(pow(pos.y,2)/PI),m) - sin(pos.z)*pow(sin(pow(pos.z,2)/PI),m) ;
	return answ;
}

const string Michalewicz::name()
{
	return "Michalewicz Function ";
}

const BENCHMARK_FUNCTION Michalewicz::getBenchmarkFunctionType()
{
	return MICHALEWICZ;
}

const SceneConfig Michalewicz::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 0.05;
	config.distance = 85;
	config.nearZPlane = 0.1f;
	config.farZPlane = 200.0f;
	return config;
}

BenchmarkPositionGenerator* Michalewicz::createPositionGenerator()
{
	return new Position3DGenerator(0,PI);
}

Goldstein::Goldstein()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Goldstein::evaluate(const Vector3d& pos)
{
	double answ1,answ2;
	answ1 = 1 + pow(pos.x + pos.y + 1,2)*(19 - 14*pos.x + 3*pow(pos.x,2) -14*pos.y + 6*pos.x*pos.y + 3*pow(pos.y,2));
	answ2 = 30 + pow(2*pos.x - 3*pos.y,2)*(18 - 32*pos.y + 12*pow(pos.x,2) + 48*pos.x -36*pos.x*pos.y + 27*pow(pos.x,2));
	return answ1*answ2;
}

const string Goldstein::name()
{
	return "Goldstein Function ";
}

const BENCHMARK_FUNCTION Goldstein::getBenchmarkFunctionType()
{
	return GOLDSTEIN;
}

const SceneConfig Goldstein::getSceneConfigForBenchmark()
{
	SceneConfig config;
	config.chartTickRate = 20;
	config.distance = 1000;
	config.nearZPlane = 0.1f;
	config.farZPlane = 5000.0f;
	return config;
}

BenchmarkPositionGenerator *Goldstein::createPositionGenerator()
{
	return new Position2DGenerator(-2,2);
}

BenchmarkFunctionFactory::BenchmarkFunctionFactory(){}

Benchmark* BenchmarkFunctionFactory::createNextFunction(BENCHMARK_FUNCTION currentFunction)
{
	switch(currentFunction)
	{
		case DEJONGF1:
			return createDeJongF5();
		break;
		case DEJONGF5:
			return createRastrigin();
		break;
		case RASTRIGIN:
			return createSchwefel(); 
		break;
		case SCHWEFEL:
			return createGriewank();
		break;
		case GRIEWANK:
			return createSalomon();
		break;
		case SALAMON:
			return createAckley();
		break;
		case ACKLEY:
			return createCamel();
		break;
		case CAMEL:
			return createShubert();
		break;
		case SHUBERT:
			return createHimmelblau();
		break;
		case HIMMELBLAU:
			return createRosenbrock();
		break;
		case ROSENBROCK:
			return createDropwave();
		break;
		case DROPWAVE:
			return createEasom();
		break;
		case EASOM:
			return createBranins();
		break;
		case BRANINS:
			return createMichalewicz();
		break;
		case MICHALEWICZ:
			return createGoldstein();
		break;
		case GOLDSTEIN:
			return createDeJongF1();
		break;
		default:
			return createDeJongF1();
		  break;
	}
}

Benchmark* BenchmarkFunctionFactory::createDeJongF1()
{
	return new DeJongF1();
}

Benchmark *BenchmarkFunctionFactory::createDeJongF5()
{
	return new DeJongF5();
}

Benchmark *BenchmarkFunctionFactory::createRastrigin()
{
	return new Rastrigin();
}

Benchmark *BenchmarkFunctionFactory::createSchwefel()
{
	return new Schwefel();
}

Benchmark *BenchmarkFunctionFactory::createGriewank()
{
	return new Griewank();
}

Benchmark *BenchmarkFunctionFactory::createSalomon()
{
	return new Salomon();
}

Benchmark *BenchmarkFunctionFactory::createAckley()
{
	return new Ackley();
}

Benchmark *BenchmarkFunctionFactory::createCamel()
{
	return new Camel();
}

Benchmark *BenchmarkFunctionFactory::createShubert()
{
	return new Shubert();
}

Benchmark *BenchmarkFunctionFactory::createHimmelblau()
{
	return new Himmelblau();
}

Benchmark *BenchmarkFunctionFactory::createRosenbrock()
{
	return new Rosenbrock();
}

Benchmark *BenchmarkFunctionFactory::createDropwave()
{
	return new DropWave();
}

Benchmark *BenchmarkFunctionFactory::createEasom()
{
	return new Easom();
}

Benchmark *BenchmarkFunctionFactory::createBranins()
{
	return new Branins();
}

Benchmark *BenchmarkFunctionFactory::createMichalewicz()
{
	return new Michalewicz();
}

Benchmark *BenchmarkFunctionFactory::createGoldstein()
{
	return new Goldstein();
}
