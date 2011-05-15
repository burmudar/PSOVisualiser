#include "PSOStructures.h"
#include "BenchFunctions.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cmath>

using namespace std;

const int PARTICLES = 10;
BenchmarkFunctionFactory* functionFactory = NULL;

Benchmark* createBenchmarkFunc()
{
	Benchmark* function = NULL;
	BenchmarkFunctionFactory* functionFactory = new BenchmarkFunctionFactory();
	function = functionFactory->createDeJongF1();
	return function;
}

void print_benchmark_choices(BenchmarkDescription* benchmarks)
{
	cout << "Please choose a function the swarm must find the global optimum for:" << endl;
	for(int i = 0; i < 16; i++)
	{
		cout << benchmarks[i].function_type << " : " << benchmarks[i].benchmark_name << endl;
	}
	cout << "17: Exit" << endl;
	cout << "Choice: __" << "\033[2D";
}

void run_pso(BasePSO* pso)
{
	PSOPerformanceStats* stats = new PSOPerformanceStats();
	pso->initialize();
	cout << endl;
	cout << "Running Swarm on function: " << pso->getFunctionName() << endl;
	for(int i = 0; i < 100; i++)
	{
		cout << "\033[0G";
		pso->updateSwarmMovement();
		cout << "Global Optimum:" << pso->global_best.fitness;
		if(pso->isSwarmBestAtOptimum())
		{
			cout << " Optimum: Yes ";
		}
		else
		{
			cout << " Optimum: No ";
		}
		stats->measure(pso);
	}
	cout << endl << endl;
	delete pso;
	delete stats;
}

void main_loop()
{
	BenchmarkDescription* benchmarks = functionFactory->getBenchmarkDescriptionArray();
	int choice = 0;
	PSOFactory* pso_factory = new PSOFactory(0.51,0.42,PARTICLES);
	while(choice != 17)
	{
		print_benchmark_choices(benchmarks);
		cin >> choice;
		if(choice < 17)
		{
			Benchmark* function = NULL;
			BenchmarkFunctionFactory* functionFactory = new BenchmarkFunctionFactory();
			function = functionFactory->createNextFunction(benchmarks[choice--].function_type);
			run_pso(pso_factory->createNormalPSO(function));
			//no need to delete function since the pso destructor deletes it in any case
		}
	}
	delete[] benchmarks;
	delete pso_factory;
}

int main(int argc,char* argv[])
{
	BenchmarkFunctionFactory* functionFactory = new BenchmarkFunctionFactory();
	main_loop();
	delete functionFactory;
	return 0;
}
