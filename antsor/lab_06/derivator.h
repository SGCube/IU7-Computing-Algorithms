#ifndef DERIVATOR_H
#define DERIVATOR_H

#include "pointlist.h"

class Derivator
{
public:
	Derivator() = delete;
	
	static double diff_left(const PointList& plist, size_t index);
	static double diff_right(const PointList& plist, size_t index);
	static double diff_center(const PointList& plist, size_t index);
	
	static double raise_exp_left(const PointList& plist);
	static double raise_exp_right(const PointList& plist);
	
	static double diff_runge(const PointList& plist, size_t index, int p);
	static double diff_runge_l(const PointList& plist, size_t index, int p);
	static double diff_level(const PointList& plist, size_t i, double a0, double a1);
	
private:
	static double difference(const Point& p1, const Point& p2);
	static double raise_exp(const Point& p1, const Point& p2, const Point& p3);
	static double runge(double left, double right, double r, int p);
	
	static double diff_ksi(double x);
	static double diff_etta_from_ksi(double a0, double a1);
	static double diff_etta_from_y(double y);
};

#endif // DERIVATOR_H
