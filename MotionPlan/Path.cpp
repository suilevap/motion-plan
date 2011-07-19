#include "StdAfx.h"
#include "Path.h"

Path::Path(std::vector<Point> points)
{
	_points = points;
}

Path::~Path(void)
{
}

std::vector<Point>& Path::GetPoints()
{
	return _points;
}

Path* Path::Empty()
{
	//TODO: optimaze
	return  new Path(std::vector<Point>());
}
Point Path::GetPoint(int index)
{
	Point result;
	if ((index<_points.size()) && (index >= 0))
	{
		result = _points[index];
	}
	else
	{
		if (index<0)
		{
			result = _points[0];
		}
		else
		{
			result = _points.back();
		}

	}
	return result;
}

int Path::Count()
{
	return _points.size();
}
