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

Rastrigin::Rastrigin()
{
	info = "x^2 + y^2 + z^2 + ... + n^2 where n is the dimensions";
}

double Rastrigin::evaluate(const Vector3d& pos)
{
	double answ;
	answ += pow(pos.x,2) + 10*cos(2*PI*pos.x)+10; 
	answ += pow(pos.y,2) + 10*cos(2*PI*pos.y)+10; 
	answ += pow(pos.z,2) + 10*cos(2*PI*pos.z)+10; 
	return answ;
}

const string Rastrigin::name()
{
	return "Rastrigin Function";
}

Schwefel::Schwefel()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Schwefel::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ += -1*pos.x*sin(sqrt(abs(pos.x)));
	answ += -1*pos.y*sin(sqrt(abs(pos.y)));
	answ += -1*pos.z*sin(sqrt(abs(pos.z)));
	return -418.9829*3 + answ;
}

const string Schwefel::name()
{
	return "Schwefel Function";
}

Griewank::Griewank()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Griewank::evaluate(const Vector3d& pos)
{
	double answ1 = 1/4000;
	answ1 += pow(pos.x,2);
	answ1 += pow(pos.y,2);
	answ1 += pow(pos.z,2);
	double answ2 = 0;	
	answ2 *= cos(pos.x / sqrt(1));
	answ2 *= cos(pos.y / sqrt(2));
	answ2 *= cos(pos.z / sqrt(3));
	return answ1-answ2+1;
}

const string Griewank::name()
{
	return "Griewank Function";
}

Salomon::Salomon()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Salomon::evaluate(const Vector3d& pos)
{
	double answ1 = 0;
	answ1 += pow(pos.x,2);
	answ1 += pow(pos.y,2);
	answ1 += pow(pos.z,2);
	answ1 = -cos(2*PI*sqrt(answ1));
	double answ2 = 0;	
	answ2 += pow(pos.x,2)+1;
	answ2 += pow(pos.y,2)+1;
	answ2 += pow(pos.z,2)+1;
	answ2 = 0.1*sqrt(answ2);
	return answ1+answ2;
}

const string Salomon::name()
{
	return "Salomon Function";
} 

DeJong * createFunction(const int& f)
{
	switch(f)
	{
		case 1:
			return new DeJongF1;
		case 2:
			return new DeJongF5;
		case 3:
			return new DeJongF5;
		case 4:
			return new Rastrigin;
		case 5:
			return new Schwefel;
		case 6:
			return new Griewank;
		case 7:
			return new Salomon;
	}
	return new DeJongF1;
}
