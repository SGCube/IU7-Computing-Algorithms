#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>

#include "point.hpp"

class PointList
{
public:
	PointList();
	PointList(std::ifstream& fin);
	
	void loadFromFile(std::ifstream& fin);
	void fill(const Point& p);
	void clear();
	
	size_t size();
	Point& operator[](size_t index);
	const Point& operator[](size_t index) const;
	
	friend std::ostream& operator<<(std::ostream& stream, const PointList& list);
	
private:
	Point* data_;
	size_t size_;
	
	void allocate();
};

#endif // MATRIX_H
