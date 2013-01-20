#ifndef CONSOLEUTIL_H_
#define CONSOLEUTIL_H_

#include <iostream>
#include "BenchFunctions.h"
#include "PSOStructures.h"

class PSOInitializer
{
public:
	BasePSO* getPSO();
	PSOInitializer();
	~PSOInitializer();
private:
	void setup_PSO(BasePSO*& pso);
	void print_benchmark_choices(BenchmarkDescription* benchmarks);
	void print_pso_choices();
	void print_particle_choices();
	void print_and_setGlobalCoeff();
	void print_and_setLocalCoeff();
	void set_benchmark(BenchmarkFunctionFactory* functionFactory,BenchmarkDescription* benchmarks,int choice);
	void set_particles(int choice);
	BasePSO* create_pso(int choice);
	void set_benchmark(int choice);
	void do_benchmark_choices();
	void do_particle_choices();
	void do_pso_choice(BasePSO*& pso);
	double getInertia();
	double getConstriction();
	Benchmark* FUNCTION;
	int PARTICLES;
	int ITERATIONS;
	double LOCAL_COEFF;
	double GLOBAL_COEFF;
};
#endif
