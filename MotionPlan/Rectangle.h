#pragma once

#ifndef MOTIONPLAN_ASTAR_RECTANGLE_H
#define MOTIONPLAN_ASTAR_RECTANGLE_H

#include <algorithm>
#include <vector>

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
    Point<CoordType> GetSize() {return (_rightBottomPoint - _leftTopPoint);}


    bool IsNeighbor(Rectangle<CoordType>* rect, CoordType step);
    Rectangle<CoordType> GetIntersection(Rectangle<CoordType>* rect, CoordType step);
    Rectangle<CoordType> GetUnion(Rectangle<CoordType>* rect);

    Rectangle(Point<CoordType> point1, Point<CoordType> point2);

    bool IsEmpty(CoordType stepSize);

    Rectangle() 
    {
        _leftTopPoint = Point<CoordType>::Zero();
        _rightBottomPoint = Point<CoordType>::Zero();
        _center = Point<CoordType>::Zero();
    }

    bool IsInside(const Point<CoordType>& point);

    //TODO: better move to ...somewhere
    Point<CoordType> GetLeftRot(Point<CoordType> x)
    {
        Point<CoordType> result;
        Point<CoordType>& lt = GetLeftTopPoint();
        CoordType triArea = lt.TriArea(x, GetRightBottomPoint());
        if (triArea >= 0)
        {
            result = GetLeftTopPoint();
        }
        else
        {
            result = GetRightBottomPoint();
        }
        return result;
    }
    Point<CoordType> GetRightRot(Point<CoordType> x)
    {
        Point<CoordType> result;
        Point<CoordType>& lt = GetLeftTopPoint();
        CoordType triArea = lt.TriArea(x, GetRightBottomPoint());
        if (triArea < 0)
        {
            result = GetLeftTopPoint();
        }
        else
        {
            result = GetRightBottomPoint();
        }
        return result;
    }

};

#include "Rectangle.inl"

}

#endif //MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
