#ifndef BENCHFUNCTIONS_H_
#define BENCHFUNCTIONS_H_

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include "gfxstructures.h"
#include "boost/random.hpp"

const double PI = 3.14159265358979323846;

enum BENCHMARK_FUNCTION {DEJONGF1,DEJONGF5,RASTRIGIN,SCHWEFEL,GRIEWANK,SALAMON,ACKLEY,CAMEL,SHUBERT,HIMMELBLAU,ROSENBROCK,DROPWAVE,EASOM,BRANINS,MICHALEWICZ,GOLDSTEIN};

class BenchmarkPositionGenerator
{
public:
	virtual	Vector3d generatePosition() = 0;
	virtual ~BenchmarkPositionGenerator();
protected:
	BenchmarkPositionGenerator(double min, double max);
	boost::variate_generator<boost::mt19937&, boost::uniform_real<double> > *generator;
	boost::mt19937 *rng;
	boost::uniform_real<double> *distribution;
};

class Position2DGenerator:public BenchmarkPositionGenerator
{
public:
	Position2DGenerator(double min, double max);
	~Position2DGenerator(){}
	virtual Vector3d generatePosition();
};

class Position3DGenerator:public BenchmarkPositionGenerator
{
public:
	Position3DGenerator(double min, double max);
	~Position3DGenerator(){}
	virtual Vector3d generatePosition();
};

class CamelPositionGenerator:public BenchmarkPositionGenerator
{
public:
	CamelPositionGenerator(double min1,double max1,double min2,double max2);
	~CamelPositionGenerator();
	virtual Vector3d generatePosition();
protected:
	boost::variate_generator<boost::mt19937&,boost::uniform_real<double> > *generator2;	
};

class Benchmark
{
public:
	virtual double evaluate(const Vector3d& pos) = 0;
	virtual const std::string name() = 0;
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType() = 0;
	virtual const SceneConfig getSceneConfigForBenchmark() = 0;
	virtual BenchmarkPositionGenerator* createPositionGenerator() =0;
	virtual ~Benchmark(){}
};

class DeJongF1:public Benchmark 
{
public:
	DeJongF1();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~DeJongF1(){}
private:
		std::string info;
};

class DeJongF5:public Benchmark
{
public:
	DeJongF5();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~DeJongF5(){}
private:
		int a[2][25];
		std::string info;
};

class Rastrigin:public Benchmark 
{
public:
	Rastrigin();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Rastrigin(){}
private:
		std::string info;
};

class Schwefel:public Benchmark 
{
public:
	Schwefel();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Schwefel(){}
private:
		std::string info;
};

class Griewank:public Benchmark 
{
public:
	Griewank();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator *createPositionGenerator(); 
	~Griewank(){}
private:
		std::string info;
};

class Salomon:public Benchmark 
{
public:
	Salomon();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator *createPositionGenerator(); 
	~Salomon(){}
private:
		std::string info;
};

class Ackley:public Benchmark 
{
public:
	Ackley();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Ackley(){}
private:
		std::string info;
};

class Camel:public Benchmark 
{
public:
	Camel();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Camel(){}
private:
		std::string info;
};

class Shubert:public Benchmark 
{
public:
	Shubert();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Shubert(){}
private:
		std::string info;
};

class Himmelblau:public Benchmark 
{
public:
	Himmelblau();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Himmelblau(){}
private:
		std::string info;
};

class Rosenbrock:public Benchmark 
{
public:
	Rosenbrock();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Rosenbrock(){}
private:
		std::string info;
};

class DropWave:public Benchmark 
{
public:
	DropWave();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~DropWave(){}
private:
		std::string info;
};

class Easom:public Benchmark 
{
public:
	Easom();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Easom(){}
private:
		std::string info;
};

class Branins:public Benchmark 
{
public:
	Branins();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Branins(){}
private:
		std::string info;
};

class Michalewicz:public Benchmark 
{
public:
	Michalewicz();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Michalewicz(){}
private:
		std::string info;
};

class Goldstein:public Benchmark 
{
public:
	Goldstein();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	virtual const BENCHMARK_FUNCTION getBenchmarkFunctionType();
	virtual const SceneConfig getSceneConfigForBenchmark();
	virtual BenchmarkPositionGenerator* createPositionGenerator(); 
	~Goldstein(){}
private:
		std::string info;
};

class BenchmarkFunctionFactory
{
public:
	BenchmarkFunctionFactory();
	~BenchmarkFunctionFactory(){}
	Benchmark* createNextFunction(BENCHMARK_FUNCTION currentFunction);
	Benchmark* createDeJongF1();
	Benchmark* createDeJongF5();
	Benchmark* createRastrigin();
	Benchmark* createSchwefel();
	Benchmark* createGriewank();
	Benchmark* createSalomon();
	Benchmark* createAckley();
	Benchmark* createCamel();
	Benchmark* createShubert();
	Benchmark* createHimmelblau();
	Benchmark* createRosenbrock();
	Benchmark* createDropwave();
	Benchmark* createEasom();
	Benchmark* createBranins();
	Benchmark* createMichalewicz();
	Benchmark* createGoldstein();
};

#endif
