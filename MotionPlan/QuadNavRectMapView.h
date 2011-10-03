#pragma once

#ifndef MOTIONPLAN_QUADNAVRECTMAPVIEW_H_
#define MOTIONPLAN_QUADNAVRECTMAPVIEW_H_

#include <vector>

#include "NavigationRectangle.h"
#include "NavRectMapView.h"
#include "GridMapView.h"
#include "Rectangle.h"


template<class CellType, typename CoordType = float>
class QuadNavRectMapView: 
    public AStar::NavRectMapView<CellType, CoordType>
{
typedef AStar::NavRectMapView<CellType, CoordType> base;
protected:
    std::vector<AStar::Rectangle<CoordType>> LoadFrom(GridMapView<CellType, CoordType>* map);
    void AddQuadsFrom(Point<CoordType> point1, Point<CoordType> point2, std::vector<AStar::Rectangle<CoordType>>* rects, GridMapView<CellType, CoordType>* map);
    QuadNavRectMapView() {}
public:
    static QuadNavRectMapView<CellType, CoordType>* Create(GridMapView<CellType, CoordType>* fromMap);

};

#include "QuadNavRectMapView.inl"

#endif//MOTIONPLAN_QUADNAVRECTMAPVIEW_H_