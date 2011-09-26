#pragma once

#ifndef MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
#define MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H

#include <vector>
#include "FastVector.h"
#include "EdgeInfo.h"
#include "Point.h"
#include "Rectangle.h"


namespace AStar
{

template<
	typename PointT, 
	typename CellType, 
	typename CostInfo = float> 
class NavigationRectangle : public Rectangle<PointT>
{	
protected:
    CellType _value;

    std::vector<EdgeInfo<int, CostInfo>> _links;
    int _index;

public:
    CellType GetValue() { return _value;}
    void SetValue(CellType value) { _value = value;}
    std::vector<EdgeInfo<int, CostInfo>>* GetNeighboors() { return &(_links); };
    int GetId() { return _index;}

    void FindNeighbors(std::vector<NavigationRectangle<PointT, CellType, CostInfo>*> navRects);

    NavigationRectangle(Point<PointT> point1, Point<PointT> point2, int index, CellType value);
    NavigationRectangle(Rectangle<PointT>& rect, int index, CellType value);
    NavigationRectangle(){}


};

#include "NavigationRectangle.inl"


}

#endif //MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
