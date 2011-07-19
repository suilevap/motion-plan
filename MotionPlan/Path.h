#pragma once

#include <vector>
#include "Point.h"
#include "Scalable.h"

class Path
{
private:
	std::vector<Point> _points;
	
public:
	Path(std::vector<Point> points);
	~Path(void);
	std::vector<Point>& GetPoints();
	Point GetPoint(int index);
	int Count();	

	static Path* Empty();
	
};
