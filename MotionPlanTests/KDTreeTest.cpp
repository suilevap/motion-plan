#include "gtest/gtest.h"
#include "KDTree.h"
#include "Rectangle.h"


TEST(KDTree, Get)
{
    AStar::KDTree<float> tree;
    std::vector<AStar::Rectangle<float>> rects;

    rects.push_back(AStar::Rectangle<float>(Point<float>(1,1),Point<float>(3,3)));
    rects.push_back(AStar::Rectangle<float>(Point<float>(4,2),Point<float>(6,4)));
    rects.push_back(AStar::Rectangle<float>(Point<float>(6,5),Point<float>(8,8)));
    rects.push_back(AStar::Rectangle<float>(Point<float>(1,8),Point<float>(5,8)));
    rects.push_back(AStar::Rectangle<float>(Point<float>(1,5),Point<float>(2,7)));
    for (int i=0; i<rects.size(); ++i)
    {
        tree.Add(rects[i], i+1);
    }
    tree.Build();

    int id;
    id = tree.GetId(Point<float>(2,2));
    EXPECT_EQ(id, 1);
    id = tree.GetId(Point<float>(5,3));
    EXPECT_EQ(id, 2);
    id = tree.GetId(Point<float>(7,6));
    EXPECT_EQ(id, 3);
    id = tree.GetId(Point<float>(7,7));
    EXPECT_EQ(id, 3);
    id = tree.GetId(Point<float>(1.5,5.5));
    EXPECT_EQ(id, 5);

    id = tree.GetId(Point<float>(4,6));
    EXPECT_EQ(id, -1);
    id = tree.GetId(Point<float>(7,2));
    EXPECT_EQ(id, -1);
}
