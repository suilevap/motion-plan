#include "gtest/gtest.h"
#include "GridMapView.h"
#include "Point.h"


TEST(GridMapViewTest, SetGetCellPoint)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	map->SetCellPoint(Point<float>(1,1), 10);
	ASSERT_EQ(10, map->GetCellPoint(Point<float>(1,1)));
	delete map;
}

TEST(GridMapViewTest, SetGetCellPointRegion)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(2,2)));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(2,3)));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(3,2)));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(3,3)));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(3,4)));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(4,3)));
	EXPECT_EQ(12, map->GetCellPoint(Point<float>(4,4)));
	delete map;

}

TEST(GridMapViewTest, Clear)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2,2));
	ASSERT_EQ(12, map->GetCellPoint(Point<float>(3,3)));
	map->Clear(0,1);
	EXPECT_EQ(0, map->GetCellPoint(Point<float>(3,3)));
	EXPECT_EQ(0, map->GetCellPoint(Point<float>(1,3)));
	delete map;
}

TEST(GridMapViewTest, GetDistanceField)
{
	GridMapView<int>* map = new GridMapView<int>(14, 14);
	//map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
    map->SetCellPoint(Point<float>(0,0), 1);

    map->SetCellPoint(Point<float>(4,5), 1);

//===========================
//0 1 1 1 1 1 1 1 1 1 1 1 1 1
//1 1 2 2 2 2 2 2 2 2 2 2 2 1
//1 2 2 3 3 3 3 3 3 3 3 3 2 1
//1 2 2 2 2 2 2 3 4 4 4 3 2 1
//1 2 2 1 1 1 2 3 4 5 4 3 2 1
//1 2 2 1 0 1 2 3 4 5 4 3 2 1
//1 2 2 1 1 1 2 3 4 5 4 3 2 1
//1 2 2 2 2 2 2 3 4 5 4 3 2 1
//1 2 3 3 3 3 3 3 4 5 4 3 2 1
//1 2 3 4 4 4 4 4 4 5 4 3 2 1
//1 2 3 4 4 4 4 4 4 4 4 3 2 1
//1 2 3 3 3 3 3 3 3 3 3 3 2 1
//1 2 2 2 2 2 2 2 2 2 2 2 2 1
//1 1 1 1 1 1 1 1 1 1 1 1 1 1
//========================
    GridMapView<int>* distFieldMap = map->GetDistanceField();
    ASSERT_TRUE(distFieldMap != NULL);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(0,0)),0);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(1,1)),1);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(0,1)),1);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(1,0)),1);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(2,2)),2);

    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(4,5)),0);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(3,5)),1);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(3,4)),1);
    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(4,4)),1);

    EXPECT_EQ(distFieldMap->GetCellPoint(Point<float>(9,4)),5);

    //distFieldMap->ToOutput();

	delete map;
	delete distFieldMap;
}
