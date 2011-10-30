#include "gtest/gtest.h"
#include "GridMapView.h"
#include "FieldNavRectMapView.h"
#include "Point.h"
#include "FastVector.h"
#include "EdgeInfo.h"
#include "BasePathFinder.h"


TEST(FieldNavRectMapView, Create)
{
	GridMapView<int>* map = new GridMapView<int>(14, 14);
	//map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
    map->SetCellPoint(Point<float>(0,0), 1);

    map->SetCellPoint(Point<float>(4,5), 1);

    FieldNavRectMapView<int>* navMap = NULL;
    navMap = FieldNavRectMapView<int>::Create(map);
    //quadMap
    //.111122
    //5111122
    //4444.22
    //3333322
    //3333322
    ASSERT_TRUE(navMap != NULL);
    EXPECT_EQ(navMap->GetMaxNode(), 6);

    //FastVector<AStar::EdgeInfo<int, float>> neighbors;
    //quadMap->GetNeighbors(1, neighbors);
    //EXPECT_EQ(neighbors.size(), 3);
    //quadMap->GetNeighbors(2, neighbors);
    //EXPECT_EQ(neighbors.size(), 3);
    //quadMap->GetNeighbors(3, neighbors);
    //EXPECT_EQ(neighbors.size(), 5);
    //quadMap->GetNeighbors(4, neighbors);
    //EXPECT_EQ(neighbors.size(), 4);
    //quadMap->GetNeighbors(5, neighbors);
    //EXPECT_EQ(neighbors.size(), 4);
    //quadMap->GetNeighbors(6, neighbors);
    //EXPECT_EQ(neighbors.size(), 3);

    //map->ToOutput();
    //navMap->ToOutput();
	delete map;
	delete navMap;
}

TEST(FieldNavRectMapView, Corridor2)
{
	GridMapView<int>* map = new GridMapView<int>(4, 2);
	//map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
    map->SetCellPoint(Point<float>(0,1), 1);
    map->SetCellPoint(Point<float>(3,0), 1);


    FieldNavRectMapView<int>* navMap = NULL;
    navMap = FieldNavRectMapView<int>::Create(map);

    ASSERT_TRUE(navMap != NULL);
 

    //map->ToOutput();
    navMap->ToOutput();
	delete map;
	delete navMap;
}

TEST(FieldNavRectMapView, FindPath)
{
	GridMapView<int>* map = new GridMapView<int>(5, 4);
	//map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
    //11.11
    //11.11
    //22222
    //22222
    map->SetCellPoint(Point<float>(2,0), 1);
    map->SetCellPoint(Point<float>(2,1), 1);


    FieldNavRectMapView<int>* navMap = NULL;
    navMap = FieldNavRectMapView<int>::Create(map);

    ASSERT_TRUE(navMap != NULL);
    navMap->ToOutput();
    
    AStar::BasePathFinder<Point<float>, int, float>* pathFinder = 
        new AStar::BasePathFinder<Point<float>, int, float>(navMap);

	AStar::Path<Point<float>>* path;

    path = pathFinder->Find(Point<float>(0,0), Point<float>(4,0));
	ASSERT_EQ(4, path->Count());
	delete path;

	delete pathFinder;

    //map->ToOutput();
    navMap->ToOutput();
	delete map;
	delete navMap;
}
