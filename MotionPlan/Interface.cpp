#include "stdafx.h"
//TODO: move GM Interface to different lib
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

#include "Interface.h"

#include "ObjectIdPool.h"
//#include "Transformable.h"
//#include "Scalable.h"


ObjectIdPool<GridMapView<int>> _maps;
ObjectIdPool<AStar::PathFinder<Point<float>, int, int, float>> _pathFinders;
ObjectIdPool<AStar::Path<Point<float>>> _paths;

char* ConvertToGmPath(AStar::Path<Point<float>>* p);

#ifdef USE_GMAPI
gm::CGMAPI* _gmapi;

double InitGM()
{
	unsigned long gmInit;
	_gmapi = gm::CGMAPI::Create( &gmInit );;
	return static_cast<double>(gmInit);
}

double CloseGM()
{
	_gmapi->Destroy();
	return 0;
}

char* GetGmPath(double pathIndex)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	AStar::Path<Point<float>>* p = _paths.Get(pathIndex2);
	char * buffer = ConvertToGmPath(p);
	return buffer;
}

double ConvertToGmPath(double pathIndex, double gmPathId)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int gmPathId2 = static_cast<int>(gmPathId);

	AStar::Path<Point<float>>* path = _paths.Get(pathIndex2);	
	std::vector<Point<float>> points = path->GetPoints();
	double x;
	double y;
	for (std::vector<Point<float>>::iterator it = points.begin(); it != points.end(); ++it)
	{
		x = it->X;
		y = it->Y;
		gm::path_add_point(gmPathId2, x, y, 100);
	}
	return path->Count();
}
#endif


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

double CreateMap(double width, double height, double cellSize)
{

	int cellSize2 = static_cast<int>(cellSize);

	GridMapView<int>* map = new GridMapView<int>(width, height, cellSize);

	int result = _maps.Add(map);

	return static_cast<double>(result);
}

double CreateHexMap(double width, double height, double cellSize)
{

	int cellSize2 = static_cast<int>(cellSize);

	GridMapView<int>* map = new HexGridMapView<int>(width, height, cellSize);

	int result = _maps.Add(map);

	return static_cast<double>(result);
}


double SetCellMap(double mapIndex, double x, double y, double cell)
{
	int mapIndex2 = static_cast<int>(mapIndex);

	int cell2 = static_cast<int>(cell);
	GridMapView<int>* map = _maps.Get(mapIndex2);
	if (map!= NULL)
	{
		Point<float> p(x, y);
		map->SetCellPoint(p, cell2);
	}
	return cell;
}

double SetCellMapRegion(double mapIndex, double x, double y, double w, double h, double cell)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	int cell2 = static_cast<int>(cell);
	GridMapView<int>* map = _maps.Get(mapIndex2);
	if (map!= NULL)
	{
		map->SetCellRegion(Point<float>(x, y), cell2, Point<float>(w, h));
	}
	return cell;
}

double GetCellMap(double mapIndex, double x, double y)
{
	int result = 0;
	int mapIndex2 = static_cast<int>(mapIndex);

	GridMapView<int>* map = _maps.Get(mapIndex2);
	if (map != NULL)
	{
		result = map->GetCellPoint(Point<float>(x, y));
	}
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

	GridMapView<int>* map = _maps.Get(mapIndex2);

	if (map != NULL)
	{
		AStar::BasePathFinder<Point<float>, int, float>* pathFinder = 
			new AStar::BasePathFinder<Point<float>, int, float>(map);
		//AStar::PathFinder<Point<float>, int, int, float>* pathFinder = 
		//	new AStar::BidirectionalPathFinder<Point<float>, int, float>(map);

		result = _pathFinders.Add(pathFinder);
	}
	return static_cast<double>(result);
}

double CreatePathFinderDebug(double mapIndex, double mapDebugIndex)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	int mapDebugIndex2 = static_cast<int>(mapDebugIndex);

	int result = -1;

	GridMapView<int>* map = _maps.Get(mapIndex2);
	GridMapView<int>* mapDebug = _maps.Get(mapDebugIndex2);


	if (map != NULL)
	{
		//AStar::BasePathFinder<Point<float>, int, float>* pathFinder = new AStar::BasePathFinder<Point<float>, int, float>(map);
		AStar::PathFinder<Point<float>, int, int, float>* pathFinder = 
			new AStar::BidirectionalPathFinder<Point<float>, int, float>(map);

#ifdef _DEBUG
		pathFinder->InitDebug(mapDebug);
#endif
		result = _pathFinders.Add(pathFinder);
	}
	return static_cast<double>(result);
}


double FindPath(double pathFinderIndex, double x, double y, double goalX, double goalY)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);

	int result = -1;
	AStar::PathFinder<Point<float>, int, int, float>* pathFinder  = _pathFinders.Get(pathFinderIndex2);

	if (pathFinder != NULL)
	{

		AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(x, y), Point<float>(goalX, goalY));

		//TODO: change to matrix transformation 
		result = _paths.Add(path);
	}
	return static_cast<double>(result);
}

double DestroyPathFinder(double pathFinderIndex)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);

	double result = _pathFinders.Free(pathFinderIndex2)? 1.0: 0.0;
	return result;
}

double GetXPath(double pathIndex, double n)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int n2 = static_cast<int>(n);

	double result = -1;
	AStar::Path<Point<float>>* path = _paths.Get(pathIndex2);
	if (path!= NULL)
	{
		Point<float> point = path->GetPoint(n2);
		result = point.X;
	}
	return static_cast<double>(result);
}
double GetYPath(double pathIndex, double n)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int n2 = static_cast<int>(n);

	double result = -1;
	AStar::Path<Point<float>>* path = _paths.Get(pathIndex2);
	if (path!= NULL)
	{
		Point<float> point = path->GetPoint(n2);
		result = point.Y;
	}
	return static_cast<double>(result);
}

double GetNPath(double pathIndex)
{
	int pathIndex2 = static_cast<int>(pathIndex);

	int result = -1;
	AStar::Path<Point<float>>* path = _paths.Get(pathIndex2);
	if (path!= NULL)
	{
		result = path->Count();
	}
	return static_cast<double>(result);
}

//only for GM
char* ConvertToGmPath(AStar::Path<Point<float>>* path)
{
	static char* format = "path_add_Point<float>(argument0, %8.2f, %8.2f, 100);\n";
	std::vector<Point<float>> points = path->GetPoints();
	int estimatedLength = points.size() * (strlen(format)+2*16);
	char* buffer = new char[estimatedLength];
	int offset=0;
	for (std::vector<Point<float>>::iterator it = points.begin(); it != points.end(); ++it)
	{
		offset += sprintf_s(buffer+offset, estimatedLength-offset, format, it->X, it->Y);
	}
	return buffer;
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

	//GridMapView<int> m(10,10);
	//for (double i = 0; i < n; ++i)
	//{
	//	int x = static_cast<int>(GetXPath(path, i)/cellSize);
	//	int y = static_cast<int>(GetYPath(path, i)/cellSize);
	//	m.SetCell(x, y, static_cast<int>(i)+1);
	//}
	//m.ToOutput();

	////TODO: AAAaa
	//GridMapView<int>* map2 = _maps.Get(map)->GetItem();
	//map2->ToOutput();

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
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
		//char* pathOutput = ConvertToGmPath(_paths.Get(static_cast<int>(path)));
		//printf(pathOutput);

		//TODO: AAAaa
		GridMapView<int>* mapObst = _maps.Get(static_cast<int>(map));
		mapObst->ToOutput();
		/*Map<float>* mapDist = _pathFinders.Get(AStar::BasePathFinder<Point<float>, int, float>)->GetItem()->GetMapDist();
		mapDist->ToOutput();*/

		GridMapView<int> m(mapObst->GetMaxPoint().X, mapObst->GetMaxPoint().Y, mapObst->GetCellSize().X);
		double n = static_cast<int>(GetNPath(path));
		for (double i = 0; i < n; ++i)
		{
			float x = GetXPath(path, i);
			float y = GetYPath(path, i);
			m.SetCellPoint(Point<float>(x, y), (static_cast<int>(i+1))%100);
		}
		m.ToOutput();

	}

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
#ifdef _DEBUG
	DestroyMap(mapDebug);
#endif
}

double Test()
{
	return 8;
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
		//char* pathOutput = ConvertToGmPath(_paths.Get(path));
		//printf(pathOutput);

		//TODO: AAAaa
		GridMapView<int>* mapObst = _maps.Get(static_cast<int>(map));
		mapObst->ToOutput();

		HexGridMapView<int> m(mapObst->GetMaxPoint().X, mapObst->GetMaxPoint().Y, mapObst->GetCellSize().Y);
		double n = static_cast<int>(GetNPath(path));
		for (double i = 0; i < n; ++i)
		{
			float x = GetXPath(path, i);
			float y = GetYPath(path, i);
			m.SetCellPoint(Point<float>(x, y), (static_cast<int>(i))%10+1);
		}
		m.ToOutput();

	}

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
#ifdef _DEBUG
	DestroyMap(mapDebug);
#endif
}
