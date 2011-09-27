#pragma once

#ifndef MOTIONPLAN_QUADNAVRECTMAPVIEW_H_
#define MOTIONPLAN_QUADNAVRECTMAPVIEW_H_

#include <vector>

#include "NavigationRectangle.h"
#include "NavRectMapView.h"
#include "GridMapView.h"

template<class CellType, typename CoordType = float>
class QuadNavRectMapView: 
    public AStar::NavRectMapView<CoordType, CellType>
{
typedef AStar::NavRectMapView<CoordType, CellType> base;
protected:
    std::vector<Rectangle<CoordType>> LoadFrom(GridMapView<CellType, CoordType>* map);
    AddQuadsFrom(Point<CoordType>& point1, Point<CoordType>& point2, std::vector<Rectangle<CoordType>>* rects, GridMapView<CellType, CoordType>* map)

public:
    QuadNavRectMapView(GridMapView<CellType, CoordType>* fromMap);

}

#include "QuadNavRectMapView.inl"

#endif//MOTIONPLAN_QUADNAVRECTMAPVIEW_H_