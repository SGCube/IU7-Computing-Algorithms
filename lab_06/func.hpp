#ifndef FUNC_HPP
#define FUNC_HPP

#include <cmath>

namespace RealFunc
{
	const double a0 = 1, a1 = 2, a2 = 3;
	
	double func(double x)
	{
		return a0 * x / (a1 + a2 * x);
	}
	
	double diff_real(double x)
	{
		return (a0 * a1) / pow(a1 + a2 * x, 2);
	}
}

#endif // FUNC_HPP
