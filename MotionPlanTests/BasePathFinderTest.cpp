#include "gtest/gtest.h"
#include "GridMapView.h"
#include "BasePathFinder.h"
#include "Point.h"
#include "Path.h"


TEST(PathFinder, PathFindPathExsist)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	AStar::BasePathFinder<Point<float>, int, float>* pathFinder = new AStar::BasePathFinder<Point<float>, int, float>(map);

	AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(0,0), Point<float>(9,9));
	ASSERT_EQ(10, path->Count());
	delete path;
	delete pathFinder;
	delete map;
	//map->SetCellRegion(Point<float>(5,0), 12, Point<float>(1,10));

}

TEST(PathFinder, PathFindPathNotExsist)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	map->SetCellRegion(Point<float>(5,0), 1, Point<float>(1,10));

	AStar::BasePathFinder<Point<float>, int, float>* pathFinder = new AStar::BasePathFinder<Point<float>, int, float>(map);

	AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(0,0), Point<float>(9,9));
	ASSERT_EQ(0, path->Count());
	delete path;
	delete pathFinder;
	delete map;
}

TEST(PathFinder, PathFindStartNotExsist)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);

	AStar::BasePathFinder<Point<float>, int, float>* pathFinder = new AStar::BasePathFinder<Point<float>, int, float>(map);

	AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(-2,0), Point<float>(9,9));
	ASSERT_EQ(0, path->Count());
	delete path;
	delete pathFinder;
	delete map;
}

TEST(PathFinder, PathFindGoalNotExsist)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);

	AStar::BasePathFinder<Point<float>, int, float>* pathFinder = new AStar::BasePathFinder<Point<float>, int, float>(map);

	AStar::Path<Point<float>>* path = pathFinder->Find(Point<float>(0,0), Point<float>(12,9));
	ASSERT_EQ(0, path->Count());
	delete path;
	delete pathFinder;
	delete map;
}