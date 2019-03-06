#include <cmath>
#include <iostream>
#include <fstream>
using namespace std;

#include "func.h"

double func(double x)
{
	return x * x + 2;
}

void file_func(double a, double b, int n)
{
	if (n > 0)
	{
		ofstream f;
		f.open("data.txt");
		if (!f.is_open())
			return;
		
		f << n << endl;
		
		double h = (b - a) / n;
		while (a <= b + h)
		{
			f << a << func(a) << endl;
			a += h;
		}
		
		f.close();
	}
}
