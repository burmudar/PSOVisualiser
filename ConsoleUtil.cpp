#include "ConsoleUtil.h"

using namespace std;

PSOInitializer::PSOInitializer()
{
	FUNCTION = NULL;
	PARTICLES = 1000;
	ITERATIONS = 1000;
	LOCAL_COEFF = 0.41;
	GLOBAL_COEFF = 0.51;
}

PSOInitializer::~PSOInitializer()
{
}

BasePSO* PSOInitializer::getPSO()
{
	BasePSO* pso = NULL;
	setup_PSO(pso);
	pso->print_information();
	return pso;
}

void PSOInitializer::setup_PSO(BasePSO*& pso)
{
	do_benchmark_choices();
	do_particle_choices();
	print_and_setGlobalCoeff();
	print_and_setLocalCoeff();
	do_pso_choice(pso);
}

void PSOInitializer::print_benchmark_choices(BenchmarkDescription* benchmarks)
{
	cout << "Please choose a function the swarm must find the global optimum for:" << endl;
	for(int i = 0; i < 16; i++)
	{
		cout << benchmarks[i].function_type << " : " << benchmarks[i].benchmark_name << endl;
	}
	cout << "17: Exit" << endl;
	cout << "Choice: __" << "\033[2D";
}

void PSOInitializer::set_benchmark(BenchmarkFunctionFactory* functionFactory,BenchmarkDescription* benchmarks,int choice)
{
	FUNCTION = functionFactory->createNextFunction(benchmarks[choice].function_type);
}

void PSOInitializer::do_benchmark_choices()
{
	BenchmarkFunctionFactory* functionFactory = new BenchmarkFunctionFactory();
	BenchmarkDescription* benchmarks = functionFactory->getBenchmarkDescriptionArray();
	print_benchmark_choices(benchmarks);
	int choice;
	cin >> choice;
	set_benchmark(functionFactory,benchmarks,choice);
}


void PSOInitializer::print_particle_choices()
{
	cout << "Please select the size of the swarm:" << endl;
	cout << "[1] 100" << endl;
	cout << "[2] 1000" << endl;
	cout << "[3] 10000" << endl;
	cout << "[4] 100000" << endl;
	cout << "Choice: ";
}

void PSOInitializer::set_particles(int choice)
{
	switch(choice)
	{
		case 1:
		{
			PARTICLES = 100;
		}
		break;
		case 2:
		{
			PARTICLES = 1000;
		}
		break;
		case 3:
		{
			PARTICLES = 10000;
		}
		break;
		case 4:
		{
			PARTICLES = 100000;
		}
		break;
		default:
		{
			PARTICLES = 10;
		}
		break;
	}
}

void PSOInitializer::do_particle_choices()
{
	print_particle_choices();
	int choice;
	cin >> choice;
	set_particles(choice);
}

void PSOInitializer::print_pso_choices()
{
	cout << "Please select the pso algorithm to use" << endl;
	cout << "[1] Normal PSO" << endl;
	cout << "[2] Inertia PSO" << endl;
	cout << "[3] Constriction PSO" << endl;
	cout << "Choice: [ ]" << "\033[2D";
}

double PSOInitializer::getInertia()
{
	cout << "Please set the inertia value"<< endl;
	cout << "Inertia: ";
	double inertia = 0.00;
	while(cin >> inertia == false)
	{
		cerr << "The value provided was incorrect. Please try again";
		cout << "Inertia: ";
	}
	return inertia;
}

double PSOInitializer::getConstriction()
{
	cout << "Please set the constriction value"<< endl;
	cout << "constriction coeffiction: ";
	double constriction = 0.00;
	while(cin >> constriction == false)
	{
		cout << endl;
		cerr << "The value provided was incorrect. Please try again";
		cout << "constriction coeffiction: ";
	}
	return constriction;
}

BasePSO* PSOInitializer::create_pso(int choice)
{
	assert(FUNCTION != NULL);
	PSOFactory* pso_factory = new PSOFactory(GLOBAL_COEFF,LOCAL_COEFF,PARTICLES);
	BasePSO* new_pso = NULL;
	switch(choice)
	{
		case 2:
		{
			double inertia = getInertia();
			new_pso = pso_factory->createInertiaPSO(inertia,FUNCTION);
		}
		break;
		case 3:
		{
			double constriction_coeff = getConstriction();
			new_pso = pso_factory->createConstrictionPSO(constriction_coeff,FUNCTION);
		}
		break;
		default:
		{
			new_pso = pso_factory->createNormalPSO(FUNCTION);
		}
		break;
	}
	delete pso_factory;
	return new_pso;
}

void PSOInitializer::do_pso_choice(BasePSO*& pso)
{
	print_pso_choices();
	int choice;
	cin >> choice;
	pso = create_pso(choice);
	pso->print_information();
}

void PSOInitializer::print_and_setGlobalCoeff()
{
	cout << "Please set the global coefficient:" << endl;
	cout << "[1] Default (" << GLOBAL_COEFF << ")"<<endl;
	cout << "[2] Specify value" << endl; 
	cout << "Choice: [ ]" << "\033[2D";
	int choice;
	while(cin >> choice == false)
	{
		cout << endl;
		cerr << "Your choice was incorrect. Please try again" << endl;
		cout << "Choice: [ ]" << "\033[2D";
	}
	if(choice == 2)
	{
		cout << "Global coefficient: ";
		while(cin >> GLOBAL_COEFF == false)
		{
			cout << endl;
			cerr << "The value provided was incorrect. Please try again" << endl;
			cout << "Global coefficient: ";
		}
	}
}

void PSOInitializer::print_and_setLocalCoeff()
{
	cout << "Please set the local coefficient:" << endl;
	cout << "[1] Default (" << LOCAL_COEFF << ")"<<endl;
	cout << "[2] Specify value" << endl; 
	cout << "Choice: [ ]" << "\033[2D";
	int choice;
	while(cin >> choice == false)
	{
		cout << endl;
		cerr << "Your choice was incorrect. Please try again" << endl;
		cout << "Choice: [ ]" << "\033[2D";
	}
	if(choice == 2)
	{
		cout << "Local coefficient: ";
		while(cin >> LOCAL_COEFF == false)
		{
			cout << endl;
			cerr << "The value provided was incorrect. Please try again" << endl;
			cout << "Local coefficient: ";
		}
	}
}

