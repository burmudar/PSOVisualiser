#ifndef DEJONGFUNCTIONS_H_
#define DEJONGFUNCTIONS_H_

#include <iostream>
#include <cmath>
#include <string>
#include "gfxmath.h"

const double PI = 3.14159265358979323846;

class DeJong
{
public:
	virtual double evaluate(const Vector3d& pos) = 0;
	virtual const std::string name() = 0;
	virtual ~DeJong(){}
};

class DeJongF1:public DeJong 
{
public:
	DeJongF1();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~DeJongF1(){}
private:
		std::string info;
};

class DeJongF5:public DeJong
{
public:
	DeJongF5();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~DeJongF5(){}
private:
		int a[2][25];
		std::string info;
};

class Rastrigin:public DeJong 
{
public:
	Rastrigin();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Rastrigin(){}
private:
		std::string info;
};

class Schwefel:public DeJong 
{
public:
	Schwefel();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Schwefel(){}
private:
		std::string info;
};

class Griewank:public DeJong 
{
public:
	Griewank();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Griewank(){}
private:
		std::string info;
};

class Salomon:public DeJong 
{
public:
	Salomon();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Salomon(){}
private:
		std::string info;
};

class Ackley:public DeJong 
{
public:
	Ackley();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Ackley(){}
private:
		std::string info;
};

class Camel:public DeJong 
{
public:
	Camel();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Camel(){}
private:
		std::string info;
};

class Shubert:public DeJong 
{
public:
	Shubert();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Shubert(){}
private:
		std::string info;
};

class Himmelblau:public DeJong 
{
public:
	Himmelblau();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Himmelblau(){}
private:
		std::string info;
};

class Rosenbrock:public DeJong 
{
public:
	Rosenbrock();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Rosenbrock(){}
private:
		std::string info;
};

class DropWave:public DeJong 
{
public:
	DropWave();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~DropWave(){}
private:
		std::string info;
};

class Easom:public DeJong 
{
public:
	Easom();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Easom(){}
private:
		std::string info;
};

class Branins:public DeJong 
{
public:
	Branins();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Branins(){}
private:
		std::string info;
};

class Michalewicz:public DeJong 
{
public:
	Michalewicz();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Michalewicz(){}
private:
		std::string info;
};

class Goldstein:public DeJong 
{
public:
	Goldstein();
	virtual double evaluate(const Vector3d& pos);
	virtual const std::string name();
	~Goldstein(){}
private:
		std::string info;
};

DeJong * createFunction(const int& f);
#endif
