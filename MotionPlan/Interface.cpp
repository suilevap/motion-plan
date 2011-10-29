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
#include "SparseGridMapView.h"
#include "NavRectMapView.h"
#include "QuadNavRectMapView.h"
#include "FieldNavRectMapView.h"


#include "Interface.h"

#include "ObjectIdPool.h"
//#include "Transformable.h"
//#include "Scalable.h"

#pragma warning( disable : 4244 )

ObjectIdPool<AStar::MapView<Point<float>,int, float>> _maps;
ObjectIdPool<AStar::PathFinder<Point<float>, int, float>> _pathFinders;
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
double ConvertPathToGmPath(AStar::Path<Point<float>>* path, int gmPathId)
{
	std::vector<Point<float>>& points = path->GetPoints();
	double x;
	double y;
	for (std::vector<Point<float>>::iterator it = points.begin(); it != points.end(); ++it)
	{
		x = it->X;
		y = it->Y;
		gm::path_add_point(gmPathId, x, y, 100);		
	}
	return path->Count();
}

double ConvertToGmPath(double pathIndex, double gmPathId)
{
	int pathIndex2 = static_cast<int>(pathIndex);
	int gmPathId2 = static_cast<int>(gmPathId);

	AStar::Path<Point<float>>* path = _paths.Get(pathIndex2);	
    double result = ConvertPathToGmPath(path, gmPathId2);
    return result;
}

double DrawMap(double mapIndex)
{
    AStar::MapView<Point<float>, int>* map0 = _maps.Get(static_cast<int>(mapIndex));
    GridMapView<int>* map = dynamic_cast<GridMapView<int>*>(map0);
    if (map != NULL)
    {
        Point<float> maxP = map->GetMaxPoint();
        Point<float> size = map->GetCellSize();
        Point<float> p;
        for (p.X = 0; p.X < maxP.X; p.X += size.X)
        {
            for (p.Y = 0; p.Y < maxP.Y; p.Y += size.Y)
            {
                int cell = map->GetCellPoint(p);
                gm::draw_rectangle_color(p.X,p.Y,p.X+size.X, p.Y + size.Y, 5, 5, 5, 5, (cell==0)?true:false);
            }
        }
    }
    return 0;
}
double DrawNavRectMap(double mapIndex)
{
    AStar::MapView<Point<float>, int>* map0 = _maps.Get(static_cast<int>(mapIndex));
    AStar::NavRectMapView<int>* map = dynamic_cast<AStar::NavRectMapView<int>*>(map0);
    if (map != NULL)
    {
        float mapDist = AStar::DistanceEvaluator::EuclideanDistance<float>(
            Point<float>::Zero(), map->GetMaxPoint());
        gm::draw_set_color(gm::c_red);
        int count = map->GetMaxNode();
        for (int i = 1; i < count; ++i)
        {
            AStar::NavigationRectangle<float, int, float>* rect = map->GetNavRect(i);
            
            Point<float> size = rect->GetSize();
            float r = min(size.X, size.Y)/2;
            float rectDist = AStar::DistanceEvaluator::EuclideanDistance<float>(
                rect->GetLeftTopPoint(), rect->GetRightBottomPoint()); 
            gm::draw_set_alpha(rectDist/mapDist);

            gm::draw_rectangle_color( rect->GetLeftTopPoint().X+2, rect->GetLeftTopPoint().Y+2,
                rect->GetRightBottomPoint().X-2, rect->GetRightBottomPoint().Y-2,
                1, 1, 1, 1, true);

            //gm::draw_circle( rect->GetCenter().X, rect->GetCenter().Y, r, 1);
            std::vector<AStar::EdgeInfo<int, float>>* edges = rect->GetNeighboors();
            int count = edges->size();
            for (int i = 0; i < count; ++i)
            {
                AStar::EdgeInfo<int, float> edgeTo1 = edges->at(i);
                AStar::NavigationRectangle<float, int, float>* rectTo1 = map->GetNavRect(edgeTo1.To);
                AStar::Rectangle<float> intersectionTo1 = rect->GetIntersection(rectTo1, 4);
                //Point<float> size = intersectionTo1.GetSize();
                //float r = max(size.X, size.Y)/2;
                float r = 4;
                gm::draw_circle( intersectionTo1.GetCenter().X, intersectionTo1.GetCenter().Y, r, 1);
                //gm::draw_rectangle_color( 
                //    intersectionTo1.GetLeftTopPoint().X, intersectionTo1.GetLeftTopPoint().Y,
                //    intersectionTo1.GetRightBottomPoint().X, intersectionTo1.GetRightBottomPoint().Y,
                //    1, 1, 1, 1, true);
                
                for (int k = i+1; k < count; ++k)
                {
                    AStar::EdgeInfo<int, float> edgeTo2 = edges->at(k);
                    AStar::NavigationRectangle<float, int, float>* rectTo2 = map->GetNavRect(edgeTo2.To);
                    AStar::Rectangle<float> intersectionTo2 = rect->GetIntersection(rectTo2, 1);
                    float d = AStar::DistanceEvaluator::EuclideanDistance<float>(
                        intersectionTo1.GetCenter(), intersectionTo2.GetCenter());
                    gm::draw_set_alpha(d/rectDist);
                    gm::draw_line(
                        intersectionTo1.GetCenter().X, intersectionTo1.GetCenter().Y,
                        intersectionTo2.GetCenter().X, intersectionTo2.GetCenter().Y);                   
                }

            }
        }
        gm::draw_set_alpha(1);
        gm::draw_set_color(gm::c_black);
    }

    return 0;
}

#endif

double CreateMap(double width, double height, double cellSize)
{

	GridMapView<int>* map = new GridMapView<int>(width, height, cellSize);

	int result = _maps.Add(map);

	return static_cast<double>(result);
}

double CreateHexMap(double width, double height, double cellSize)
{

	GridMapView<int>* map = new HexGridMapView<int>(width, height, cellSize);

	int result = _maps.Add(map);

	return static_cast<double>(result);
}

double CreateSparseMap(double width, double height, double cellSize)
{

	GridMapView<int>* map = new SparseGridMapView<int>(width, height, cellSize);

	int result = _maps.Add(map);

	return static_cast<double>(result);
}

double CreateQuadMap(double gridMapIndex)
{
    AStar::MapView<Point<float>, int>* gridMap0 = _maps.Get(static_cast<int>(gridMapIndex));
    GridMapView<int>* gridMap = dynamic_cast<GridMapView<int>*>(gridMap0);

    //QuadNavRectMapView<int, float>* map = QuadNavRectMapView<int, float>::Create(gridMap);
    FieldNavRectMapView<int, float>* map = FieldNavRectMapView<int, float>::Create(gridMap);

	int result = _maps.Add(map);

	return static_cast<double>(result);
}

double SetCellMap(double mapIndex, double x, double y, double cell)
{
	int mapIndex2 = static_cast<int>(mapIndex);

	int cell2 = static_cast<int>(cell);
	AStar::MapView<Point<float>, int>* map = _maps.Get(mapIndex2);
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
	AStar::MapView<Point<float>, int>* map = _maps.Get(mapIndex2);
	if (map!= NULL)
	{
		Point<float> pointStart(x, y);
		Point<float> size(w, h);
		map->SetCellRegion(pointStart, cell2, size);
	}
	return cell;
}

double GetCellMap(double mapIndex, double x, double y)
{
	int result = 0;
	int mapIndex2 = static_cast<int>(mapIndex);

	AStar::MapView<Point<float>, int>* map = _maps.Get(mapIndex2);
	if (map != NULL)
	{
		Point<float> point(x, y);
		result = map->GetCellPoint(point);
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

	AStar::MapView<Point<float>, int>* map = _maps.Get(mapIndex2);

	if (map != NULL)
	{
   //     GridMapView<int>* gridMap = dynamic_cast<GridMapView<int>*>(map);
   //     QuadNavRectMapView<int, float>* quadMap = QuadNavRectMapView<int, float> ::Create(gridMap);
   //     _maps.Add(quadMap);
   //     AStar::BasePathFinder<Point<float>, int, float>* pathFinder = 
			//new AStar::BasePathFinder<Point<float>, int, float>(quadMap);

		AStar::BasePathFinder<Point<float>, int, float>* pathFinder = 
			new AStar::BasePathFinder<Point<float>, int, float>(map);

		/*AStar::PathFinder<Point<float>, int, int, float>* pathFinder = 
			new AStar::BidirectionalPathFinder<Point<float>, int, float>(map);*/

		result = _pathFinders.Add(pathFinder);
	}
	return static_cast<double>(result);
}

double CreatePathFinderDebug(double mapIndex, double mapDebugIndex)
{
	int mapIndex2 = static_cast<int>(mapIndex);
	int mapDebugIndex2 = static_cast<int>(mapDebugIndex);

	int result = -1;

	AStar::MapView<Point<float>, int>* mapDebug = _maps.Get(mapDebugIndex2);

	int pathFinderIndex = static_cast<int>(CreatePathFinder(mapIndex2));

	if (mapDebug != NULL)
	{

#ifdef _DEBUG
		AStar::PathFinder<Point<float>, int, float>* pathFinder = _pathFinders.Get(pathFinderIndex);
		pathFinder->InitDebug(mapDebug);
#endif
		result = pathFinderIndex;
	}
	return static_cast<double>(result);
}


double FindPath(double pathFinderIndex, double x, double y, double goalX, double goalY)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);

	int result = -1;
	AStar::PathFinder<Point<float>, int, float>* pathFinder  = _pathFinders.Get(pathFinderIndex2);

	if (pathFinder != NULL)
	{

		AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(x, y), Point<float>(goalX, goalY));

		result = _paths.Add(path);
	}
	return static_cast<double>(result);
}

double FindPathGM(double pathFinderIndex, double x, double y, double goalX, double goalY, double gmPath)
{
	int pathFinderIndex2 = static_cast<int>(pathFinderIndex);

	double result = -1;
	AStar::PathFinder<Point<float>, int, float>* pathFinder  = _pathFinders.Get(pathFinderIndex2);

	if (pathFinder != NULL)
	{

		AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(x, y), Point<float>(goalX, goalY));
        gm::path_clear_points(gmPath);
		result = ConvertPathToGmPath(path, static_cast<int>(gmPath));
        delete path;
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

double Test()
{
	return 8;
}

void OutputPath(double mapObstInd, double path)
{
    //char* pathOutput = ConvertToGmPath(_paths.Get(static_cast<int>(path)));
    //printf(pathOutput);

    //TODO: AAAaa
    AStar::MapView<Point<float>, int>* mapObst0 = _maps.Get(static_cast<int>(mapObstInd));
    GridMapView<int>* mapObst = dynamic_cast<GridMapView<int>*>(mapObst0);

    mapObst->ToOutput();
    /*Map<float>* mapDist = _pathFinders.Get(AStar::BasePathFinder<Point<float>, int, float>)->GetItem()->GetMapDist();
    mapDist->ToOutput();*/

    GridMapView<int> m(mapObst->GetMaxPoint().X, mapObst->GetMaxPoint().Y, mapObst->GetCellSize().X);
    double n = static_cast<int>(GetNPath(path));
    for (double i = 0; i < n; ++i)
    {
	    float x = GetXPath(path, i);
	    float y = GetYPath(path, i);
		Point<float> point(x, y);
	    m.SetCellPoint(point, (static_cast<int>(i+1))%100);
    }
    m.ToOutput();

}

#pragma warning( default : 4244 )

