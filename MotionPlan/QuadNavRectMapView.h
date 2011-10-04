#pragma once

#ifndef MOTIONPLAN_QUADNAVRECTMAPVIEW_H_
#define MOTIONPLAN_QUADNAVRECTMAPVIEW_H_

#include <vector>

#include "NavigationRectangle.h"
#include "NavRectMapView.h"
#include "GridMapView.h"
#include "Rectangle.h"


template<class CellType, typename CoordType = float, bool UseFastNodeSearch = false>
class QuadNavRectMapView: 
    public AStar::NavRectMapView<CellType, CoordType>
{
typedef AStar::NavRectMapView<CellType, CoordType> base;

protected:
    class QuadTreeNode
    {
    public:
        int NavRectId;
        QuadTreeNode* Childs[4];

        QuadTreeNode* GetChild(Point<CoordType>& point, Point<CoordType>& center)
        {
            int i = (point.X >= center.X ? 1 : 0) + (point.Y >= center.Y ? 1 : 0)*2;
            return Childs[i];
        }
        QuadTreeNode()
        {
            NavRectId = -1;
            for (int i =0; i <4; i++)
            {
                Childs[i] = NULL;
            }
        }
        ~QuadTreeNode()
        {
            for (int i = 0; i <4; i++)
            {
                if (Childs[i] != NULL)
                {
                    delete Childs[i];
                }
            }
        }        
    };

    QuadTreeNode* _root;

    Point<CoordType> _cellSize;

    GridMapView<int, CoordType>* _fastNodeSearch;

    std::vector<AStar::Rectangle<CoordType>> LoadFrom(GridMapView<CellType, CoordType>* map);

    QuadTreeNode* 
        AddQuadsFrom(Point<CoordType> point1, Point<CoordType> point2, std::vector<AStar::Rectangle<CoordType>>* rects, GridMapView<CellType, CoordType>* map);

    QuadNavRectMapView() {}

public:
    virtual int GetNode(Point<CoordType>& point);

    static QuadNavRectMapView<CellType, CoordType, UseFastNodeSearch>* Create(GridMapView<CellType, CoordType>* fromMap);

    ~QuadNavRectMapView() 
    {
        delete _root;
        if (UseFastNodeSearch)
        {
            delete _fastNodeSearch;
        }
    }

};

#include "QuadNavRectMapView.inl"

#endif//MOTIONPLAN_QUADNAVRECTMAPVIEW_H_