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

const string DeJongF1::functionDef()
{
	return "X^2 + Y^2 + Z^3";
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

const string DeJongF5::functionDef()
{
	return "0.002 + SUM<1 - 25>j + 1 / (j+(Xi + Aij)^6) where Aij is a 2 by 25 matrix with values in the following set {-32,-16,0,16,32}";
}

double DeJongF5::evaluate(const Vector3d& pos)
{
	double sumi;
	double sumj=0;
	for(unsigned int j = 0; j < 25; j++)
	{
		sumi = 0;
		for(unsigned int i = 0; i < 2; i++)
		{
			if (i == 0) sumi += pow(pos.x - a[i][j],6);
			else sumi += pow(pos.y - a[i][j],6);
		}
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
	}
	return new DeJongF1;
}
