#pragma once

#ifndef MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
#define MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H

#include <vector>
#include "FastVector.h"
#include "EdgeInfo.h"
//#include "Point.h"

namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 
	typename CostInfo = float> 
class NavigationRectangle
{	
protected:
    CellType _value;
    PointInfo _leftTopPoint;
    PointInfo _rightBottomPoint;

    std::vector<EdgeInfo<int, CostInfo>> _links;
    int _index;

public:
    PointInfo GetLeftTopPoint() { return _leftTopPoint; }
    PointInfo GetRightBottomPoint() { return _rightBottomPoint; }
    PointInfo GetCenter() {return (_leftTopPoint+_leftTopPoint) / 2;}

    CellType GetValue() { return _value;}
    void SetValue(CellType value) { _value = value;}
    std::vector<EdgeInfo<int, CostInfo>> GetNeighboors() { return _links; };
    int GetId() { return _index;}

    bool IsNeighbor(NavigationRectangle<PointInfo, CellType, CostInfo>* navRect);
    void FindNeighbors(std::vector<NavigationRectangle<PointInfo, CellType, CostInfo>*> navRects);

    NavigationRectangle(PointInfo point1, PointInfo point2);


};

#include "NavigationRectangle.inl"


}

#endif //MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
