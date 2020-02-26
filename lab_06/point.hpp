#ifndef POINT_H
#define POINT_H

struct Point
{
	double x;
	double y;
	
	Point& operator=(const Point& p)
	{
		this->x = p.x;
		this->y = p.y;
		return *this;
	}
	
	Point& operator=(Point&& p)
	{
		this->x = p.x;
		this->y = p.y;
		p.x = 0;
		p.y = 0;
		return *this;
	}
};

#endif // POINT_H
