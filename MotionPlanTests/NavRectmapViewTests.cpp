#include "gtest/gtest.h"

#include <vector>

#include "Rectangle.h"
#include "NavRectMapView.h"
#include "BasePathFinder.h"
#include "Path.h"
#include "Point.h"



TEST(NavRectMapView, Init)
{
    std::vector<AStar::Rectangle<int>> rects;

    AStar::NavRectMapView<int,int>* map;
    map = AStar::NavRectMapView<int,int>::CreateCustom(rects, 1);

    delete map;
}

TEST(NavRectMapView, OnePath)
{
    std::vector<AStar::Rectangle<int>> rects;

    rects.push_back(AStar::Rectangle<int>(Point<int>(1,1),Point<int>(3,3)));
    rects.push_back(AStar::Rectangle<int>(Point<int>(4,2),Point<int>(6,4)));
    rects.push_back(AStar::Rectangle<int>(Point<int>(6,5),Point<int>(8,8)));
    rects.push_back(AStar::Rectangle<int>(Point<int>(1,8),Point<int>(5,8)));
    rects.push_back(AStar::Rectangle<int>(Point<int>(1,5),Point<int>(2,7)));
 
    AStar::NavRectMapView<int,int>* map;
    map = AStar::NavRectMapView<int,int>::CreateCustom(rects, 1);
    //map->ToOutput();
	AStar::BasePathFinder<Point<int>, int, float>* pathFinder = 
        new AStar::BasePathFinder<Point<int>, int, float>(map);

	AStar::Path<Point<int>>* path;

    path = pathFinder->Find(Point<int>(2,2), Point<int>(2,6));
	ASSERT_EQ(5, path->Count());
	delete path;
    path = pathFinder->Find(Point<int>(2,6), Point<int>(2,2));
	ASSERT_EQ(5, path->Count());
	delete pathFinder;
	delete map;

}
