#include "stdafx.h"

#include <string>
#include <vector>
#include "Map.h"
#include "Point.h"
#include "PathPoint.h"
#include "PathFinder.h"

#include "Interface.h"

//char * data 
//	= "..#\n1.2\n###";

char* Action(char * map)
{
	std::string d = map;
	std::vector<Point> points;
	Map<int>* m = Map<int>::LoadFrom(d, &points);
	PathFinder finder(m);
	finder.Find(points[1].X, points[1].Y, points[2].X, points[2].Y);
	m->ToOutput();
	return "Hello\nWorld";
}
