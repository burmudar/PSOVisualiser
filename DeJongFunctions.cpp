#include "DeJongFunctions.h"

using namespace std;


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
					cout << a[row][col] << endl;
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
					cout << a[row][col] << endl;
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

DeJong * createFunction(const int& f)
{
	switch(f)
	{
		case 1:
			return new DeJongF1;
		case 5:
			return new DeJongF5;
		case 6:
			return new DeJongF5;
	}
	return new DeJongF1;
}
