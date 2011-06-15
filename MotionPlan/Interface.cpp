#include "stdafx.h"

#include <string>
#include <vector>
#include "Map.h"
#include "Point.h"


#include "Interface.h"


char * data 
	= "..#\n1.2\n###";

char* Action(char * map)
{
	std::string d = map;
	std::vector<Point> points;
	Map<int>* m = Map<int>::LoadFrom(d, &points);

	m->ToOutput();
	return "Hello\nWorld";
}