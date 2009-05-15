#include "gfxmath.h"
#include "PSOStructures.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int main(int argc,char* argv[])
{
	DeJong * function = createFunction(5);
	cout << function->name() << endl;
	cout << setprecision(3) << function->evaluate(Vector3d(-420.9687,-420.9687,-420.9687));
	int i;
	cin >> i;
	ConsolePSO pso = ConsolePSO(1000,7,0.41,0.52);	
	while(true)
	{
		cout << pso.global_best.fitness << endl;
		cout << pso.global_best.pos << endl;
		pso.updateSwarmMovement();
	}
	cout << pso.global_best.fitness << endl;
	return 0;
}
