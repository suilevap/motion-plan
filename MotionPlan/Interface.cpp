#include "stdafx.h"

#include <string>
#include <vector>
#include "Map.h"
#include "ScaledMap.h"
#include "Point.h"
#include "PathPoint.h"
#include "PathFinder.h"

#include "Interface.h"

//char * data 
//	= "..#\n1.2\n###";

#include "ObjectIdPool.h"

ObjectIdPool<Map<int>> _maps;
ObjectIdPool<PathFinder> _pathFinders;
ObjectIdPool<Path> _paths;

char* Action(char * map)
{
	std::string d = map;
	std::vector<Point> points;
	Map<int>* m = Map<int>::LoadFrom(d, &points);
	PathFinder finder(m);
	std::vector<Point> path = finder.Find(points[1].X, points[1].Y, points[2].X, points[2].Y)->GetPoints();
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


int CreateMap(int width, int height, float cellSize)
{
	Map<int>* map = new ScaledMap<int>(width, height, cellSize);
	int result = _maps.Add(map);
	return result;
}

int SetCellMap(int mapIndex, int x, int y, int cell)
{
	Map<int>* map = _maps.Get(mapIndex);
	map->SetCell(x, y, cell);
	return cell;
}

int GetCellMap(int mapIndex, int x, int y)
{
	Map<int>* map = _maps.Get(mapIndex);
	int result = map->GetCell(x, y);
	return result;
}

int DestroyMap(int mapIndex)
{
	return _maps.Free(mapIndex) ? 1 : 0;
}

int CreatePathFinders(int mapIndex)
{
	int result = -1;
	Map<int>* map = _maps.Get(mapIndex);
	if (map != NULL)
	{
		PathFinder* pathFinder = new PathFinder(map);
		result = _pathFinders.Add(pathFinder);
	}
	return result;
}
int FindPath(int pathFinderIndex, int x, int y, int goalX, int goalY)
{
	int result = -1;
	PathFinder* pathFinder = _pathFinders.Get(pathFinderIndex);
	if (pathFinder != NULL)
	{
		Path* path = pathFinder->Find(x, y, goalX, goalY);
		result = _paths.Add(path);
	}
	return result;
}
int DestroyPathFinders(int pathFinderIndex)
{
	return _paths.Free(pathFinderIndex)? 1: 0;
}

int GetXPath(int pathIndex, int n)
{
	int result = -1;
	Path* path = _paths.Get(pathIndex);
	if (path!= NULL)
	{
		Point p = path->GetPoint(n);
		result = p.X;
	}
	return result;
}
int GetYPath(int pathIndex, int n)
{
	int result = -1;
	Path* path = _paths.Get(pathIndex);
	if (path!= NULL)
	{
		Point p = path->GetPoint(n);
		result = p.Y;
	}
	return result;
}

int GetNPath(int pathIndex)
{
	int result = -1;
	Path* path = _paths.Get(pathIndex);
	if (path!= NULL)
	{
		result = path->Count();
	}
	return result;
}

int DestroyPath(int pathIndex)
{
	return _paths.Free(pathIndex)? 1: 0;
}