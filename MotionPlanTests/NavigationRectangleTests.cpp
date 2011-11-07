#include "gtest/gtest.h"
#include "NavigationRectangle.h"
#include "Point.h"


TEST(NavigationRectangle, CheckNeighboors)
{
    AStar::NavigationRectangle<int, int, float> rect1(Point<int>(5,5),Point<int>(15,15), 1, 0);
    AStar::NavigationRectangle<int, int, float> rect2(Point<int>(5,5),Point<int>(15,15), 2, 0);
    bool result;
    int step = 1;
    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(2,2),Point<int>(5,3), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_FALSE(result);

    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(2,2),Point<int>(5,7), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(2,10),Point<int>(5,12), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(2,16),Point<int>(5,27), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(17,17),Point<int>(25,27), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_FALSE(result);
    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(16,17),Point<int>(25,27), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_FALSE(result);
    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(16,14),Point<int>(25,27), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(10,15),Point<int>(25,27), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_TRUE(result);

    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(2,14),Point<int>(18,4), 2, 0);
    result = rect1.IsNeighbor(&rect2, step);
    EXPECT_TRUE(result);

}

TEST(NavigationRectangle, CheckIntersect)
{
    AStar::NavigationRectangle<int, int, float> rect1(Point<int>(5,5),Point<int>(15,15), 1, 0);
    AStar::NavigationRectangle<int, int, float> rect2(Point<int>(5,5),Point<int>(15,15), 2, 0);
    AStar::Rectangle<int> result;
    int step = 1;
    rect2 = AStar::NavigationRectangle<int, int, float>(Point<int>(1,6),Point<int>(6,8), 2, 0);
    result = rect1.GetIntersection(&rect2, step);
    EXPECT_EQ(5, result.GetLeftTopPoint().X);
    EXPECT_EQ(6, result.GetLeftTopPoint().Y);
    EXPECT_EQ(6, result.GetRightBottomPoint().X);
    EXPECT_EQ(8, result.GetRightBottomPoint().Y);

    

}

