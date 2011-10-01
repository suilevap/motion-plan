#include "stdafx.h"

#include "InterfaceForTest.h"

#include "Interface.h"

#include <string>
#include <vector>

#ifdef USE_GMAPI
#define GMAPI_NO_D3D
#include "gmapi.h"
#endif

#include "Point.h"
#include "PathNode.h"
#include "BasePathFinder.h"
#include "BidirectionalPathFinder.h"
#include "GridMapView.h"
#include "HexGridMapView.h"
#include "SparseGridMapView.h"

#include "Interface.h"

#include "ObjectIdPool.h"


char* Action(char * map)
{
	//std::string d = map;
	//std::vector<Point<float>> points;
	//GridMapView<int>* m = GridMapView<int>::LoadFrom(d, &points);
	//AStar::BasePathFinder<Point<float>, int, float> finder(m);
	//std::vector<Point<float>> path = finder.Find(Point<float>(points[1].X, points[1].Y), Point<float>(points[2].X, points[2].Y))->GetPoints();
	//printf("map\n");
	//m->ToOutput();
	//
	//GridMapView<int>* pathMap =  new GridMapView<int>(m->GetMaxPoint().X, m->GetMaxPoint().Y);
	//int index = 1;
	//for (std::vector<Point<float>>::iterator it = path.begin(); it != path.end(); ++it)
	//{
	//	Point<float> p = *it;
	//	pathMap->SetCellPoint(p, index++);
	//}
	//printf("path\n");
	//pathMap->ToOutput();
	//delete m;
	//delete pathMap;

	return "Hello\nWorld";
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

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
}

double GenMap(int w, int h, int cellSize)
{
    //int cellSize = 16;
    //int w = 40;
    //int h = 100;
	double map = CreateMap(w*cellSize,h*cellSize,cellSize);
	//map = CreateMap(w*cellSize,h*cellSize,cellSize);
	SetCellMap(map, 4*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 5*cellSize, 1);
	SetCellMap(map, 5*cellSize, 6*cellSize, 1);
	SetCellMap(map, 5*cellSize, 7*cellSize, 1);
	SetCellMap(map, 4*cellSize, 7*cellSize, 1);
	SetCellMapRegion(map, (w/2)*cellSize, 0*cellSize, 2*cellSize, (h*0.75)*cellSize, 1);
    return map;
}

double GenPathFinder(double map, int w, int h, int cellSize)  
{
#ifndef _DEBUG
	double pathFinder = CreatePathFinder(map);
#else
	double mapDebug = CreateMap(w*cellSize,h*cellSize,cellSize);
	double pathFinder = CreatePathFinderDebug(map, mapDebug);
#endif
    return pathFinder;
}

void FindPathTest(double map, double pathFinder, int w, int h, int cellSize, bool outputMap)
{
	double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, (w-2)*cellSize, 2.0*cellSize);
    //double path = FindPath(pathFinder, (w-2)*cellSize, 2.0*cellSize, 2.0*cellSize, 8.0*cellSize);

	if (outputMap)
	{
		OutputPath(map, path);
	}

	DestroyPath(path);
}

void TestPerformance(bool outputMap)
{
	int cellSize = 16;
	int w = 40;
	int h = 100;
	double map = CreateMap(w*cellSize,h*cellSize,cellSize);
	//map = CreateMap(w*cellSize,h*cellSize,cellSize);
	SetCellMap(map, 4*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 5*cellSize, 1);
	SetCellMap(map, 5*cellSize, 6*cellSize, 1);
	SetCellMap(map, 5*cellSize, 7*cellSize, 1);
	SetCellMap(map, 4*cellSize, 7*cellSize, 1);
	SetCellMapRegion(map, (w/2)*cellSize, 0*cellSize, 2*cellSize, (h*0.75)*cellSize, 1);
	//SetCellMapRegion(map, (w/2)*cellSize, (h/2+1)*cellSize, 2*cellSize, (h/2-2)*cellSize, 1);
#ifndef _DEBUG
	double pathFinder = CreatePathFinder(map);
#else
	double mapDebug = CreateMap(w*cellSize,h*cellSize,cellSize);
	double pathFinder = CreatePathFinderDebug(map, mapDebug);
#endif	
	double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, (w-2)*cellSize, 2.0*cellSize);

	if (outputMap)
	{
		OutputPath(map, path);
	}

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
#ifdef _DEBUG
	DestroyMap(mapDebug);
#endif
}

void TestHexPerformance(bool outputMap)
{
	int cellSize = 16;
	int w = 40;
	int h = 100;
	//w = 10;
	//h = 10;
	double map = CreateHexMap(w*cellSize,h*cellSize,cellSize);


	//map = CreateMap(w*cellSize,h*cellSize,cellSize);
	SetCellMap(map, 4*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 5*cellSize, 1);
	SetCellMap(map, 5*cellSize, 6*cellSize, 1);
	SetCellMap(map, 5*cellSize, 7*cellSize, 1);
	SetCellMap(map, 4*cellSize, 7*cellSize, 1);
	SetCellMapRegion(map, (w/2)*cellSize, 0*cellSize, 2*cellSize, (h*0.75)*cellSize, 1);
	

#ifndef _DEBUG
	double pathFinder = CreatePathFinder(map);
#else
	double mapDebug = CreateHexMap(w*cellSize,h*cellSize,cellSize);
	double pathFinder = CreatePathFinderDebug(map, mapDebug);
#endif

	
	double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, (w-2)*cellSize, 2.0*cellSize);
	//double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, (w/2)*cellSize, h/2.0*cellSize);

	if (outputMap)
	{
		OutputPath(map, path);
	}

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
#ifdef _DEBUG
	DestroyMap(mapDebug);
#endif
}


void TestSparsePerformance(bool outputMap)
{
	int cellSize = 16;
	int w = 40;
	int h = 100;
	double map = CreateSparseMap(w*cellSize,h*cellSize,cellSize);
	//map = CreateMap(w*cellSize,h*cellSize,cellSize);
	SetCellMap(map, 4*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 4*cellSize, 1);
	SetCellMap(map, 5*cellSize, 5*cellSize, 1);
	SetCellMap(map, 5*cellSize, 6*cellSize, 1);
	SetCellMap(map, 5*cellSize, 7*cellSize, 1);
	SetCellMap(map, 4*cellSize, 7*cellSize, 1);
	SetCellMapRegion(map, (w/2)*cellSize, 0*cellSize, 2*cellSize, (h*0.75)*cellSize, 1);
	//SetCellMapRegion(map, (w/2)*cellSize, (h/2+1)*cellSize, 2*cellSize, (h/2-2)*cellSize, 1);
#ifndef _DEBUG
	double pathFinder = CreatePathFinder(map);
#else
	double mapDebug = CreateMap(w*cellSize,h*cellSize,cellSize);
	double pathFinder = CreatePathFinderDebug(map, mapDebug);
#endif	
	double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, (w-2)*cellSize, 2.0*cellSize);

	if (outputMap)
	{
		OutputPath(map, path);
	}

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
#ifdef _DEBUG
	DestroyMap(mapDebug);
#endif
}
