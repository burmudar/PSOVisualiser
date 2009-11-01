#include "gfxmath.h"
#include "PSOStructures.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <time.h>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc,char* argv[])
{
	int functionnr = 1;
	if(argc < 2)
	{
		cout << "psomain2 functionnumber \n Note: fuctionnumber <= 17" << endl;
		return 1;
	}
	else
	{
		functionnr = atoi(argv[1]);
		if(functionnr < 1 || functionnr > 17)
		{
			cout << "Function number must be in range {1,17}" << endl;
			return 1;
		}
		else
		{
			DeJong * function = createFunction(functionnr);
			cout << function->name() << endl;
			cout << setprecision(3) << function->evaluate(Vector3d(0,-1,0));
			clock_t timespan = clock();
			ConsolePSO pso = ConsolePSO(1000,7,0.41,0.52,1.0);	
			ofstream graphfile;
			ostringstream filename;
			string name = function->name();
			filename << name << ".txt";
			graphfile.open(filename.str().c_str());
			for(int i =0; i < 200; i++)
			{
				cout << pso.global_best.fitness << endl;
				cout << pso.global_best.pos << endl;
				graphfile << i << "\t" << pso.global_best.fitness << "\t" << difftime(clock(),timespan) / 1000<< endl;
				pso.updateSwarmMovement();
			}
			cout << pso.global_best.fitness << endl;
			cout << filename.str() << endl;
			graphfile.close();
			delete(function);

		}
	}
		return 0;
}
