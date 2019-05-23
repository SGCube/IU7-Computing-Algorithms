#include <cmath>

#include "derivator.h"

/////////// private ///////////////////////////////////////////////////////////

double Derivator::difference(const Point& p1, const Point& p2)
{
	return (p1.y - p2.y) / (p1.x - p2.x);
}

double Derivator::raise_exp(const Point& p1, const Point& p2, const Point& p3)
{
	return (-3 * p1.y + 4 * p2.y - p3.y) / (p3.x - p1.x);
}

double Derivator::runge(double ksi, double ksir, double r, int p)
{
	return ksi + (ksi - ksir) / (pow(r, p) - 1);
}

double Derivator::diff_ksi(double x)
{
	return -1 / pow(x, 2);
}

double Derivator::diff_etta_from_ksi(double a0, double a1)
{
	return a1 / a0;
}

double Derivator::diff_etta_from_y(double y)
{
	return -1 / pow(y, 2);
}

/////////// public ////////////////////////////////////////////////////////////

double Derivator::diff_left(const PointList& plist, size_t i)
{
	return difference(plist[i], plist[i - 1]);
}

double Derivator::diff_right(const PointList& plist, size_t i)
{
	return difference(plist[i + 1], plist[i]);
}

double Derivator::diff_center(const PointList& plist, size_t i)
{
	return difference(plist[i + 1], plist[i - 1]);
}


double Derivator::raise_exp_left(const PointList& plist)
{
	return raise_exp(plist[0], plist[1], plist[2]);
}

double Derivator::raise_exp_right(const PointList& plist)
{
	size_t last = plist.size() - 1;
	return raise_exp(plist[last], plist[last - 1], plist[last - 2]);
}


double Derivator::diff_runge(const PointList& plist, size_t i, int p)
{
	double ksi = diff_right(plist, i);
	double ksir = difference(plist[i + 2], plist[i]);
	return runge(ksi, ksir, 2, p);
}

double Derivator::diff_runge_l(const PointList& plist, size_t i, int p)
{
	double ksi = diff_left(plist, i);
	double ksir = difference(plist[i], plist[i - 2]);
	return runge(ksi, ksir, 2, p);
}

double Derivator::diff_level(const PointList& plist, size_t i, double a0, double a1)
{
	double ksi = diff_ksi(plist[i].x);
	double etta_from_ksi = diff_etta_from_ksi(a0, a1);
	double etta_from_y = diff_etta_from_y(plist[i].y);

	return (ksi / etta_from_y) * etta_from_ksi;
}
