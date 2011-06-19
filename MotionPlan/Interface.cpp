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
	std::vector<Point> path = finder.Find(points[1].X, points[1].Y, points[2].X, points[2].Y);
	printf("map\n");
	m->ToOutput();
	
	Map<int>* pathMap =  new Map<int>(m->GetWidth(), m->GetHeight());
	int index = 1;
	for (std::vector<Point>::iterator it = path.begin(); it != path.end(); ++it)
	{
		pathMap->SetCell(it->X, it->Y, index++);
	}
	printf("path\n");
	pathMap->ToOutput();
	delete m;
	delete pathMap;

	return "Hello\nWorld";
}
