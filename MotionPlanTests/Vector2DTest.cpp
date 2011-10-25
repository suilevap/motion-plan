#include "gtest/gtest.h"
#include "Vector2D.h"
#include <vector>


TEST(Vector2D, CheckRegion)
{
    std::vector<int> data(100);
    data[50] = 10;
    Vector2D<int> map(data, 10);
    bool result;
    result = map.CheckRegion(0,0,9,9, bind2nd(std::equal_to<int>(),0));
    EXPECT_FALSE(result);
    result = map.CheckRegion(0,0,4,4, bind2nd(std::equal_to<int>(),0));
    EXPECT_TRUE(result);
    result = map.CheckRegion(0,0,9,9, bind2nd(std::greater<int>(),-1));
    EXPECT_TRUE(result);
}

TEST(Vector2D, FillRect)
{
    std::vector<int> data(100);
    
    Vector2D<int> map(data, 10);
    map.Data[map.GetId(5, 5)] = 1;
    int x0, y0, x1, y1;
    map.FillRect( 3, 3, bind2nd(std::equal_to<int>(),0), &x0, &y0, &x1, &y1);
    EXPECT_EQ(x0, 0);
    EXPECT_EQ(y0, 0);
    EXPECT_EQ(x1, 9);
    EXPECT_EQ(y1, 4);

}
