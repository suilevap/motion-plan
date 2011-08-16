#include "gtest/gtest.h"
#include "GridMapView.h"
#include "Point.h"


TEST(GridMapViewTest, SetGetCellPoint)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	map->SetCellPoint(Point<float>(1,1), 10);
	ASSERT_EQ(10, map->GetCellPoint(Point<float>(1,1)));
}

TEST(GridMapViewTest, SetGetCellPointRegion)
{
	GridMapView<int>* map = new GridMapView<int>(10, 10);
	map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2,2));
	ASSERT_EQ(10, map->GetCellPoint(Point<float>(3,3)));
}