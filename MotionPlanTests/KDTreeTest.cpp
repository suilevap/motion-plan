#include <time.h>

#include "gtest/gtest.h"
#include "GridMapView.h"
#include "FieldNavRectMapView.h"
#include "Point.h"
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

TEST(KDTree, Performance)
{
	GridMapView<int>* map = new GridMapView<int>(100, 100);
	//map->SetCellRegion(Point<float>(2,2), 12, Point<float>(2.5, 2.5));
    map->SetCellPoint(Point<float>(0,0), 1);
    map->SetCellPoint(Point<float>(4,5), 1);
    map->SetCellPoint(Point<float>(40,5), 1);
    map->SetCellPoint(Point<float>(4,50), 1);
    map->SetCellRegion(Point<float>(50,0), 1, Point<float>(10,2));
    map->SetCellRegion(Point<float>(25,40), 1, Point<float>(2,10));
    map->SetCellRegion(Point<float>(5,10), 1, Point<float>(10,10));

    FieldNavRectMapView<int>* navMap = NULL;
    navMap = FieldNavRectMapView<int>::Create(map);
	
    clock_t time0, time1, times;

    ASSERT_TRUE(navMap != NULL);

    times = clock();
	time0 = times;
    for (int r=1; r<10000;++r)
    {
        for (int i=0;i<100;++i)
        {
            for (int k=0;k<100;++k)
            {
                Point<float> p(i,k);
                navMap->GetNode(p);
            }
        }
        if (r%1000 == 0)
		{
            time1 = clock();
		    printf("%3dk time: %4d, avg time: %4d\n",r/1000, (time1 - time0), (time1 - times)/(r/1000) );
		    time0 = clock();
        }
    }


	delete map;
	delete navMap;
}