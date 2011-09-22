#include "gtest/gtest.h"
#include "NavigationRectangle.h"
#include "Point.h"


TEST(NavigationRectangle, CheckNeighboors)
{
    AStar::NavigationRectangle<Point<int>, int, float> rect1(Point<int>(5,5),Point<int>(15,15));
    AStar::NavigationRectangle<Point<int>, int, float> rect2(Point<int>(5,5),Point<int>(15,15));
    bool result;
    
    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(2,2),Point<int>(5,3));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_FALSE(result);

    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(2,2),Point<int>(5,7));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(2,10),Point<int>(5,12));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(2,16),Point<int>(5,27));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(17,17),Point<int>(25,27));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_FALSE(result);
    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(16,17),Point<int>(25,27));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_FALSE(result);
    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(16,14),Point<int>(25,27));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(10,15),Point<int>(25,27));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<Point<int>, int, float>(Point<int>(2,14),Point<int>(18,4));
    result = rect1.IsNeighbor(&rect2);
    EXPECT_TRUE(result);

}

