#pragma once

#ifndef MOTIONPLAN_ASTAR_RECTANGLE_H
#define MOTIONPLAN_ASTAR_RECTANGLE_H


#include "Point.h"

namespace AStar
{

template<typename PointT>
class Rectangle
{	
protected:
    Point<PointT> _leftTopPoint;
    Point<PointT> _rightBottomPoint;
    Point<PointT> _center;
public:
    Point<PointT> GetLeftTopPoint() { return _leftTopPoint; }
    Point<PointT> GetRightBottomPoint() { return _rightBottomPoint; }
    Point<PointT> GetCenter() {return _center;}

    bool IsNeighbor(Rectangle<PointT>* rect);

    Rectangle(Point<PointT> point1, Point<PointT> point2);

    Rectangle() 
    {
        _leftTopPoint = Point<PointT>::Zero();
        _rightBottomPoint = Point<PointT>::Zero();
        _center = Point<PointT>::Zero();
    }

    bool IsInside(const Point<PointT>& point);

};

#include "Rectangle.inl"

}

#endif //MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
