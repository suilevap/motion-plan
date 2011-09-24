#include "gtest/gtest.h"

#include <vector>

#include "Rectangle.h"
#include "NavRectMapView.h"
#include "Point.h"


TEST(NavRectMapView, Init)
{
    std::vector<AStar::Rectangle<int>> rects;

    AStar::NavRectMapView<int,int>* map;
    map = new AStar::NavRectMapView<int,int>(rects);

    delete map;
}

