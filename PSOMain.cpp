#include "gfxmath.h"
#include "PSOStructures.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc,char* argv[])
{
    DeJong* 	function = createFunction(5);
	cout << "Fitness:"<< function->evaluate(Vector3d(-32,-32,0,0)) << endl;
	int i;
	cin >> i;

	ConsolePSO pso = ConsolePSO(1000,5,0.41,0.52);	
	for(int i =0; i < 10000;i++)
	{
		cout << pso.global_best.fitness << endl;
		cout << pso.global_best.pos << endl;
		pso.updateSwarmMovement();
	}
	cout << pso.global_best.fitness << endl;
	return 0;
}
