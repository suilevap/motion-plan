#pragma once

#ifndef MOTIONPLAN_ASTAR_RECTANGLE_H
#define MOTIONPLAN_ASTAR_RECTANGLE_H


#include "Point.h"

namespace AStar
{

template<typename CoordType>
class Rectangle
{	
protected:
    Point<CoordType> _leftTopPoint;
    Point<CoordType> _rightBottomPoint;
    Point<CoordType> _center;
public:
    Point<CoordType> GetLeftTopPoint() { return _leftTopPoint; }
    Point<CoordType> GetRightBottomPoint() { return _rightBottomPoint; }
    Point<CoordType> GetCenter() {return _center;}

    bool IsNeighbor(Rectangle<CoordType>* rect, CoordType step);

    Rectangle(Point<CoordType> point1, Point<CoordType> point2);

    bool IsEmpty(CoordType stepSize);

    Rectangle() 
    {
        _leftTopPoint = Point<CoordType>::Zero();
        _rightBottomPoint = Point<CoordType>::Zero();
        _center = Point<CoordType>::Zero();
    }

    bool IsInside(const Point<CoordType>& point);

};

#include "Rectangle.inl"

}

#endif //MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
