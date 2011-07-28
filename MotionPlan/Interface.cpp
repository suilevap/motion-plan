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
#include "GridMapView.h"

#include "Interface.h"

#include "ObjectIdPool.h"
#include "Transformable.h"
#include "Scalable.h"



ObjectIdPool<Transformable<GridMapView<int>>> _maps;
ObjectIdPool<Transformable<AStar::BasePathFinder<Point, int, float>>> _pathFinders;
ObjectIdPool<Transformable<AStar::Path<Point>>> _paths;

char* ConvertToGmPath(Transformable<AStar::Path<Point>>* p);

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
	Transformable<AStar::Path<Point>>* p = _paths.Get(pathIndex2);
	char * buffer = ConvertToGmPath(p);
	return buffer;
}

double ConvertToGmPath(double pathIndex, double gmPathId)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int gmPathId2 = static_cast<int>(gmPathId);

	Transformable<AStar::Path<Point>>* p = _paths.Get(pathIndex2);
	AStar::Path<Point>* path = p->GetItem();
	std::vector<Point> points = path->GetPoints();
	double x;
	double y;
	for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		x = p->TransformExact(it->X+0.5);
		y = p->TransformExact(it->Y+0.5);
		gm::path_add_point(gmPathId2, x, y, 100);
	}
	return path->Count();
}
#endif


char* Action(char * map)
{
	std::string d = map;
	std::vector<Point> points;
	GridMapView<int>* m = GridMapView<int>::LoadFrom(d, &points);
	AStar::BasePathFinder<Point, int, float> finder(m);
	std::vector<Point> path = finder.Find(Point(points[1].X, points[1].Y), Point(points[2].X, points[2].Y))->GetPoints();
	printf("map\n");
	m->ToOutput();
	
	GridMapView<int>* pathMap =  new GridMapView<int>(m->GetMaxPoint().X, m->GetMaxPoint().Y);
	int index = 1;
	for (std::vector<Point>::iterator it = path.begin(); it != path.end(); ++it)
	{
		Point p = *it;
		pathMap->SetCellPoint(p, index++);
	}
	printf("path\n");
	pathMap->ToOutput();
	delete m;
	delete pathMap;

	return "Hello\nWorld";
}

double CreateMap(double width, double height, double cellSize)
{
	int width2 = static_cast<int>(width/cellSize+0.5);
	int height2 = static_cast<int>(height/cellSize+0.5);
	int cellSize2 = static_cast<int>(cellSize);

	GridMapView<int>* map = new GridMapView<int>(width2, height2);

	Transformable<GridMapView<int>>* m = new Scalable<GridMapView<int>>(map, 1.0/cellSize);
	int result = _maps.Add(m);

	return static_cast<double>(result);
}

double SetCellMap(double mapIndex, double x, double y, double cell)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	//int x2 = static_cast<int>(x);
	//int y2 = static_cast<int>(y);
	int cell2 = static_cast<int>(cell);
	Transformable<GridMapView<int>>* m = _maps.Get(mapIndex2);
	if (m!= NULL)
	{
		GridMapView<int>* map = m->GetItem();
		int x2 = m->Transform(x);
		int y2 = m->Transform(y);
		Point p(x2,y2);
		map->SetCellPoint(p, cell2);
	}
	return cell;
}

double SetCellMapRegion(double mapIndex, double x, double y, double w, double h, double cell)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	int cell2 = static_cast<int>(cell);
	Transformable<GridMapView<int>>* m = _maps.Get(mapIndex2);
	if (m!= NULL)
	{
		GridMapView<int>* map = m->GetItem();
		int x2 = static_cast<int>(m->TransformExact(x)-0.5);
		int y2 = static_cast<int>(m->TransformExact(y)-0.5);
		int w2 = static_cast<int>(m->TransformExact(w)+1);
		int h2 = static_cast<int>(m->TransformExact(h)+1);
		map->SetCellRegion(Point(x2, y2), cell2, Point(w2, h2));
	}
	return cell;
}

double GetCellMap(double mapIndex, double x, double y)
{
	int result = 0;
	int mapIndex2 = static_cast<int>(mapIndex);

	Transformable<GridMapView<int>>* m = _maps.Get(mapIndex2);
	if (m != NULL)
	{
		GridMapView<int>* map = m->GetItem();
		int x2 = m->Transform(x);
		int y2 = m->Transform(y);
		result = map->GetCellPoint(Point(x2, y2));

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

	Transformable<GridMapView<int>>* m = _maps.Get(mapIndex2);

	if (m != NULL)
	{
		GridMapView<int>* map = m->GetItem();
		AStar::BasePathFinder<Point, int, float>* pathFinder = new AStar::BasePathFinder<Point, int, float>(map);
		//TODO: change to matrix transformation 
		Transformable<AStar::BasePathFinder<Point, int, float>>* pf = new Scalable<AStar::BasePathFinder<Point, int, float>>(pathFinder, m->TransformExact(1));

		result = _pathFinders.Add(pf);
	}
	return static_cast<double>(result);
}

double FindPath(double pathFinderIndex, double x, double y, double goalX, double goalY)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);

	int result = -1;
	Transformable<AStar::BasePathFinder<Point, int, float>>* pf  = _pathFinders.Get(pathFinderIndex2);

	if (pf != NULL)
	{
		AStar::BasePathFinder<Point, int, float>* pathFinder = pf->GetItem();
		int x2 = pf->Transform(x);
		int y2 = pf->Transform(y);
		int goalX2 = pf->Transform(goalX);
		int goalY2 = pf->Transform(goalY);

		AStar::Path<Point>* path = pathFinder->Find(Point(x2, y2), Point(goalX2, goalY2));

		//TODO: change to matrix transformation 
		Transformable<AStar::Path<Point>>* p = new Scalable<AStar::Path<Point>>(path, 1 / pf->TransformExact(1));
		result = _paths.Add(p);
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

	int result = -1;
	Transformable<AStar::Path<Point>>* p = _paths.Get(pathIndex2);
	if (p!= NULL)
	{
		AStar::Path<Point>* path = p->GetItem();
		Point point = path->GetPoint(n2);
		result = p->Transform(point.X+0.5);
	}
	return static_cast<double>(result);
}
double GetYPath(double pathIndex, double n)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int n2 = static_cast<int>(n);

	int result = -1;
	Transformable<AStar::Path<Point>>* p = _paths.Get(pathIndex2);
	if (p!= NULL)
	{
		AStar::Path<Point>* path = p->GetItem();
		Point point = path->GetPoint(n2);
		result = p->Transform(point.Y+0.5);
	}
	return static_cast<double>(result);
}

double GetNPath(double pathIndex)
{
	int pathIndex2 = static_cast<int>(pathIndex);

	int result = -1;
	Transformable<AStar::Path<Point>>* p = _paths.Get(pathIndex2);
	if (p!= NULL)
	{
		AStar::Path<Point>* path = p->GetItem();
		result = path->Count();
	}
	return static_cast<double>(result);
}

//only for GM
char* ConvertToGmPath(Transformable<AStar::Path<Point>>* p)
{
	static char* format = "path_add_point(argument0, %8.2f, %8.2f, 100);\n";
	AStar::Path<Point>* path = p->GetItem();
	std::vector<Point> points = path->GetPoints();
	int estimatedLength = points.size() * (strlen(format)+2*16);
	char* buffer = new char[estimatedLength];
	int offset=0;
	for (std::vector<Point>::iterator it = points.begin(); it != points.end(); ++it)
	{
		offset += sprintf(buffer+offset, format, p->TransformExact(it->X+0.5), p->TransformExact(it->Y+0.5));
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

	double pathFinder = CreatePathFinder(map);
	
	double path = FindPath(pathFinder, 2.0*cellSize, 8.0*cellSize, (w-2)*cellSize, 2.0*cellSize);

	if (outputMap)
	{
		char* pathOutput = ConvertToGmPath(_paths.Get(path));
		printf(pathOutput);

		//TODO: AAAaa
		GridMapView<int>* mapObst = _maps.Get(map)->GetItem();
		mapObst->ToOutput();
		/*Map<float>* mapDist = _pathFinders.Get(AStar::BasePathFinder<Point, int, float>)->GetItem()->GetMapDist();
		mapDist->ToOutput();*/

		GridMapView<int> m(mapObst->GetMaxPoint().X,mapObst->GetMaxPoint().Y);
		double n = static_cast<int>(GetNPath(path));
		for (double i = 0; i < n; ++i)
		{
			int x = static_cast<int>(GetXPath(path, i)/cellSize);
			int y = static_cast<int>(GetYPath(path, i)/cellSize);
			m.SetCellPoint(Point(x, y), (static_cast<int>(i))%100+1);
		}
		m.ToOutput();

	}

	DestroyMap(map);
	DestroyPathFinder(pathFinder);
	DestroyPath(path);
}

double Test()
{
	return 8;
}
