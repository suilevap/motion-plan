#include "gtest/gtest.h"
#include "KDTree.h"
#include "Rectangle.h"


TEST(KDTree, Add)
{
    AStar::KDTree<float> tree;
    tree.Add(AStar::Rectangle<float>(Point<float>(0,0),Point<float>(10,10)),1);
    tree.Add(AStar::Rectangle<float>(Point<float>(5,0),Point<float>(10,10)),2);
    tree.Add(AStar::Rectangle<float>(Point<float>(7,5),Point<float>(10,10)),3);
    tree.Add(AStar::Rectangle<float>(Point<float>(1,2),Point<float>(3,5)),4);
    tree.Add(AStar::Rectangle<float>(Point<float>(4,2),Point<float>(5,5)),5);
    tree.Build();
}
