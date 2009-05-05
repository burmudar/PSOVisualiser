#include "DeJongFunctions.h"
#include <iostream>

using namespace std;

int main()
{
	DeJong* f = createFunction(5);
	cout << f->functionDef();
	return 0;
}
