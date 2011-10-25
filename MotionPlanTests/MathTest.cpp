#include "gtest/gtest.h"
#include "MathHelper.h"
#include "Filters.h"

TEST(MathHelper, UpperPowerOfTwoTest)
{
    //FilterNEQ<int, 4> filter;
    //bool a = filter(3);
    //a = filter(4);
    
    //std::binder2nd<std::not_equal_to<int>> f2 = bind2nd(std::not_equal_to<int>(), 4);
    //bool a = f2(3);
    //a = f2(4);

    EXPECT_EQ(16, MathHelper::UpperPowerOfTwo(10));
    EXPECT_EQ(128, MathHelper::UpperPowerOfTwo(96));
    EXPECT_EQ(256, MathHelper::UpperPowerOfTwo(129));
    EXPECT_EQ(1024, MathHelper::UpperPowerOfTwo(1000));
    EXPECT_EQ(2048, MathHelper::UpperPowerOfTwo(1500));

}

TEST(Math, UpperRankOfTwo)
{
    EXPECT_EQ(4, MathHelper::UpperRankOfTwo(10));
    EXPECT_EQ(7, MathHelper::UpperRankOfTwo(96));
    EXPECT_EQ(8, MathHelper::UpperRankOfTwo(129));
    EXPECT_EQ(10, MathHelper::UpperRankOfTwo(1000));
    EXPECT_EQ(11, MathHelper::UpperRankOfTwo(1500));
}
