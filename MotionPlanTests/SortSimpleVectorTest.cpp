#include "gtest/gtest.h"
#include "SortSimpleVector.h"

TEST(SortSimpleVector, PopIndexMax)
{
    std::vector<int> data;
    data.push_back(0);//0
    data.push_back(4);//1
    data.push_back(-1);//2
    data.push_back(3);//3
    data.push_back(5);//4
    data.push_back(2);//5
    data.push_back(1);//6

    SortSimpleVector<int> sorted(data);

    ASSERT_FALSE(sorted.Empty());
    ASSERT_EQ(sorted.PopIndexMax(),4);
    ASSERT_EQ(sorted.PopIndexMax(),1);
    ASSERT_EQ(sorted.PopIndexMax(),3);
    ASSERT_EQ(sorted.PopIndexMax(),5);
    ASSERT_EQ(sorted.PopIndexMax(),6);
    ASSERT_EQ(sorted.PopIndexMax(),0);
    ASSERT_EQ(sorted.PopIndexMax(),2);
    ASSERT_TRUE(sorted.Empty());

}
