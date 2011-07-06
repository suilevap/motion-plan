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

#include "ObjectIdPool.h"
#include "Transformable.h"
#include "Scalable.h"


ObjectIdPool<Transformable<Map<int>>> _maps;
ObjectIdPool<Transformable<PathFinder>> _pathFinders;
ObjectIdPool<Transformable<Path>> _paths;

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


double CreateMap(double width, double height, double cellSize)
{
	int width2 = static_cast<int>(width/cellSize);
	int height2 = static_cast<int>(height/cellSize);
	int cellSize2 = static_cast<int>(cellSize);

	Map<int>* map = new Map<int>(width2, height2);

	Transformable<Map<int>>* m = new Scalable<Map<int>>(map, 1.0/cellSize);
	int result = _maps.Add(m);

	return static_cast<double>(result);
}

double SetCellMap(double mapIndex, double x, double y, double cell)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	//int x2 = static_cast<int>(x);
	//int y2 = static_cast<int>(y);
	int cell2 = static_cast<int>(cell);
	Transformable<Map<int>>* m = _maps.Get(mapIndex2);

	Map<int>* map = m->GetItem();
	int x2 = m->Transform(x);
	int y2 = m->Transform(y);

	map->SetCell(x2, y2, cell2);

	return cell;
}

double GetCellMap(double mapIndex, double x, double y)
{
	int mapIndex2 = static_cast<int>(mapIndex);

	Transformable<Map<int>>* m = _maps.Get(mapIndex2);
	Map<int>* map = m->GetItem();
	int x2 = m->Transform(x);
	int y2 = m->Transform(y);

	int result = map->GetCell(x2, y2);
	return static_cast<double>(result);
}

double DestroyMap(double mapIndex)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	double result = _maps.Free(mapIndex2) ? 1.0 : 0.0;
	return result;
}

double CreatePathFinder(double mapIndex)
{
	int mapIndex2 = static_cast<int>(mapIndex);

	int result = -1;

	Transformable<Map<int>>* m = _maps.Get(mapIndex2);
	Map<int>* map = m->GetItem();

	if (map != NULL)
	{
		PathFinder* pathFinder = new PathFinder(map);
		//TODO: change to matrix transformation 
		Transformable<PathFinder>* pf = new Scalable<PathFinder>(pathFinder, m->TransformExact(1));

		result = _pathFinders.Add(pf);
	}
	return static_cast<double>(result);
}

double FindPath(double pathFinderIndex, double x, double y, double goalX, double goalY)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);


	int result = -1;
	Transformable<PathFinder>* pf  = _pathFinders.Get(pathFinderIndex2);
	PathFinder* pathFinder = pf->GetItem();
	int x2 = pf->Transform(x);
	int y2 = pf->Transform(y);
	int goalX2 = pf->Transform(goalX);
	int goalY2 = pf->Transform(goalY);

	if (pathFinder != NULL)
	{
		Path* path = pathFinder->Find(x2, y2, goalX2, goalY2);

		//TODO: change to matrix transformation 
		Transformable<Path>* p = new Scalable<Path>(path, 1 / pf->TransformExact(1));
		result = _paths.Add(p);
	}
	return static_cast<double>(result);
}
double DestroyPathFinder(double pathFinderIndex)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);

	double result = _paths.Free(pathFinderIndex2)? 1.0: 0.0;
	return result;
}

double GetXPath(double pathIndex, double n)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int n2 = static_cast<int>(n);

	int result = -1;
	Transformable<Path>* p = _paths.Get(pathIndex2);
	Path* path = p->GetItem();
	if (path!= NULL)
	{
		Point point = path->GetPoint(n2);
		result = p->Transform(point.X);
	}
	return static_cast<double>(result);
}
double GetYPath(double pathIndex, double n)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int n2 = static_cast<int>(n);

	int result = -1;
	Transformable<Path>* p = _paths.Get(pathIndex2);
	Path* path = p->GetItem();
	if (path!= NULL)
	{
		Point point = path->GetPoint(n2);
		result = p->Transform(point.Y);
	}
	return static_cast<double>(result);
}

double GetNPath(double pathIndex)
{
	int pathIndex2 = static_cast<int>(pathIndex);

	int result = -1;
	Transformable<Path>* p = _paths.Get(pathIndex2);
	Path* path = p->GetItem();
	if (path!= NULL)
	{
		result = path->Count();
	}
	return static_cast<double>(result);
}

double DestroyPath(double pathIndex)
{
	int pathIndex2 = static_cast<int>(pathIndex);

	return _paths.Free(pathIndex2)? 1.0: 0.0;
}

void TestGmInterface()
{
	int cellSize = 10;
	double map = CreateMap(10*cellSize,10*cellSize,cellSize);
	SetCellMap(map, 4*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 5*cellSize, 1);
	SetCellMap(map, 5*cellSize, 6*cellSize, 1);
	SetCellMap(map, 5*cellSize, 7*cellSize, 1);
	SetCellMap(map, 4*cellSize, 7*cellSize, 1);

	double pathFinder = CreatePathFinder(map);
	
	double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, 8.0*cellSize, 3.0*cellSize);
	double n = static_cast<int>(GetNPath(path));

	Map<int> m(10,10);
	for (double i = 0; i < n; ++i)
	{
		int x = static_cast<int>(GetXPath(path, i)/cellSize);
		int y = static_cast<int>(GetYPath(path, i)/cellSize);
		m.SetCell(x, y, static_cast<int>(i)+1);
	}
	m.ToOutput();

	//TODO: AAAaa
	Map<int>* map2 = _maps.Get(map)->GetItem();
	map2->ToOutput();

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
}