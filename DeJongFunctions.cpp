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
	double answ=0;
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
	answ += pos.x*sin(sqrt(abs(pos.x)));
	answ += pos.y*sin(sqrt(abs(pos.y)));
	answ += pos.z*sin(sqrt(abs(pos.z)));
	return 418.9829*3 - answ;
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

Ackley::Ackley()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Ackley::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ += exp(-0.2);
	answ *= sqrt(pow(pos.x,2)+pow(pos.y,2));
	answ += 3*(cos(2*pos.x)+ sin(2*pos.y));
	return answ;
}

const string Ackley::name()
{
	return "Ackley Function in 2D";
}

Camel::Camel()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Camel::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ += (4 - 2.1*pow(pos.x,2)+pow(pos.x,4)/3)*pow(pos.x,2)+(pos.x*pos.y)+(-4 +4*pow(pos.y,2))*pow(pos.y,2);
	return answ;
}

const string Camel::name()
{
	return "Six-Camel Hump Back Function ";
}

Shubert::Shubert()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Shubert::evaluate(const Vector3d& pos)
{
	double answ1 = 0;
	for (int i =1; i <=5;i++)
	{
		answ1+=i*cos((i+1)*pos.x + i);	
	}
	double answ2=0;
	for (int i =1; i <=5;i++)
	{
		answ2 += i*cos((i+1)*pos.y + i);
	}
	return answ1*answ2;
}

const string Shubert::name()
{
	return "Shubert Function ";
}

Himmelblau::Himmelblau()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Himmelblau::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ = pow((pow(pos.x,2) + pos.y - 11),2) + pow((pos.x + pow(pos.y,2) - 7),2);
	return answ;
} 
const string Himmelblau::name()
{
	return "Himmelblau Function ";
}

Rosenbrock::Rosenbrock()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Rosenbrock::evaluate(const Vector3d& pos)
{
	double answ = 0;
	answ = 100 * pow((pos.y - pow(pos.x,2)),2) + pow((1 - pos.x),2);
	answ = 100 * pow((pos.z - pow(pos.y,2)),2) + pow((1 - pos.y),2);
	return answ;
}

const string Rosenbrock::name()
{
	return "Rosenbrock Function ";
}

DropWave::DropWave()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double DropWave::evaluate(const Vector3d& pos)
{
	double answ,powsum;
	powsum = pow(pos.x,2) + pow(pos.y,2);
	answ = 1 + cos(12*sqrt(powsum));
	answ /= 0.5*powsum + 2;
	return answ;
}

const string DropWave::name()
{
	return "DropWave Function ";
}

Easom::Easom()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Easom::evaluate(const Vector3d& pos)
{
	double answ;
	answ = -cos(pos.x)*cos(pos.y)*exp(-1*pow(pos.x - PI,2) - pow(pos.y - PI,2));
	return answ;
}

const string Easom::name()
{
	return "Easom Function ";
}

Branins::Branins()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Branins::evaluate(const Vector3d& pos)
{
	double answ;
	answ = pow(pos.y - ((5.1/(4*pow(PI,2)))*pow(pos.x,2)) + (5/PI)*pos.x - 6,2) + 10*(1-(1/(8*PI)))*cos(pos.x) + 10;
	return answ;
}

const string Branins::name()
{
	return "Branins Function ";
}

Michalewicz::Michalewicz()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Michalewicz::evaluate(const Vector3d& pos)
{
	double answ,m;
	m = 20;
	answ = -sin(pos.x)*pow(sin(pow(pos.x,2)/PI),m) - sin(pos.y)*pow(sin(pow(pos.y,2)/PI),m) - sin(pos.z)*pow(sin(pow(pos.z,2)/PI),m) ;
	return answ;
}

const string Michalewicz::name()
{
	return "Michalewicz Function ";
}

Goldstein::Goldstein()
{
	info = "418.9829*n + sum(Xi*Sin(Sqrt(abs(Xi))))";
}

double Goldstein::evaluate(const Vector3d& pos)
{
	double answ1,answ2;
	answ1 = 1 + pow(pos.x + pos.y + 1,2)*(19 - 14*pos.x + 3*pow(pos.x,2) -14*pos.y + 6*pos.x*pos.y + 3*pow(pos.y,2));
	answ2 = 30 + pow(2*pos.x - 3*pos.y,2)*(18 - 32*pos.y + 12*pow(pos.x,2) + 48*pos.x -36*pos.x*pos.y + 27*pow(pos.x,2));
	return answ1*answ2;
}

const string Goldstein::name()
{
	return "Goldstein Function ";
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
		case 8:
			return new Ackley;
		case 9:
			return new Camel;
		case 10:
			return new Shubert;
		case 11:
			return new Himmelblau;
		case 12:
			return new Rosenbrock;
		case 13:
			return new DropWave;
		case 14:
			return new Easom;
		case 15:
			return new Branins;
		case 16:
			return new Michalewicz;
		case 17:
			return new Michalewicz;
	}
	return new DeJongF1;
}
