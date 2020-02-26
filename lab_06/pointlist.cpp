#include <fstream>

#include "pointlist.h"
#include "error.hpp"

PointList::PointList()
{
	size_ = 0;
	data_ = nullptr;
}

PointList::PointList(std::ifstream& fin)
{
	loadFromFile(fin);
}

void PointList::loadFromFile(std::ifstream& fin)
{
	clear();
	
	fin >> size_;
	allocate();
	
	for (size_t i = 0; i < size_; i++)
	{
		fin >> data_[i].x;
		fin >> data_[i].y;
	}
}

void PointList::allocate()
{
	if (size_ < 1)
		throw ErrorEmpty(__FILE__, typeid(PointList).name(), __FUNCTION__);
	
	data_ = new Point[size_];
	if (!data_)
		throw ErrorMemory(__FILE__, typeid(PointList).name(), __FUNCTION__);
}

void PointList::fill(const Point& p)
{
	for (size_t i = 0; i < size_; i++)
		data_[i] = p;
}

void PointList::clear()
{
	if (data_)
		delete [] data_;
	size_ = 0;
}

size_t PointList::size() const
{
	return size_;
}

Point& PointList::operator[](size_t index)
{
	return data_[index];
}

const Point& PointList::operator[](size_t index) const
{
	return data_[index];
}

std::ostream& operator<<(std::ostream& stream, const PointList& list)
{
    stream << "Point list:" << std::endl;
    
    if (list.size_ == 0)
        stream << " empty";
    else
    {
        for (size_t i = 0; i < list.size_; i++)
			stream << list.data_[i].x << ' ' << list.data_[i].y << std::endl;
    }
    return stream;
}
