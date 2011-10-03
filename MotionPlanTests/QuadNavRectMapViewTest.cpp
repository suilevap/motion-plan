#include "gtest/gtest.h"
#include "GridMapView.h"
#include "QuadNavRectMapView.h"
#include "Point.h"
#include "FastVector.h"
#include "EdgeInfo.h"



TEST(QuadNavRectMapView, Create)
{
	GridMapView<int>* map = new GridMapView<int>(4, 4);
	//map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
    map->SetCellPoint(Point<float>(0,0), 1);

    QuadNavRectMapView<int>* quadMap = NULL;
    quadMap = QuadNavRectMapView<int>::Create(map);
    //quadMap
    //.144
    //2344
    //5566
    //5566
    ASSERT_TRUE(quadMap != NULL);
    ASSERT_EQ(quadMap->GetMaxNode(), 7);

    FastVector<AStar::EdgeInfo<int, float>> neighbors;
    quadMap->GetNeighbors(1, neighbors);
    EXPECT_EQ(neighbors.size(), 3);
    quadMap->GetNeighbors(2, neighbors);
    EXPECT_EQ(neighbors.size(), 3);
    quadMap->GetNeighbors(3, neighbors);
    EXPECT_EQ(neighbors.size(), 5);
    quadMap->GetNeighbors(4, neighbors);
    EXPECT_EQ(neighbors.size(), 4);
    quadMap->GetNeighbors(5, neighbors);
    EXPECT_EQ(neighbors.size(), 4);
    quadMap->GetNeighbors(6, neighbors);
    EXPECT_EQ(neighbors.size(), 3);

    //map->ToOutput();
    //quadMap->ToOutput();
	delete map;
	delete quadMap;
}


