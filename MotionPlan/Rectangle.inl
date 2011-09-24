#ifndef MOTIONPLAN_ASTAR_RECTANGLE_H
#error "Include from Rectangle.h only."
#else

template<typename PointT>
Rectangle<PointT>::
Rectangle(Point<PointT> point1, Point<PointT> point2)
{
	_leftTopPoint = point1;
	_rightBottomPoint = point2;
    _center = Point<PointT>::Avg(point1, point2);
}

template<typename PointT>
bool Rectangle<PointT>::
IsInside(const Point<PointT>& point)
{
    return (point>_leftTopPoint && point<_rightBottomPoint);
}

template<typename PointT>
bool Rectangle<PointT>::
IsNeighbor(Rectangle<PointT>* navRect)
{
    bool result = false;
    Point<PointT> rect1Start = GetLeftTopPoint();
    Point<PointT> rect2Start = navRect->GetLeftTopPoint();
    Point<PointT> rect1End = GetRightBottomPoint();
    Point<PointT> rect2End = navRect->GetRightBottomPoint();
    result = !(rect2Start.X > rect1End.X+1 || rect2End.X < rect1Start.X-1 
        || rect2Start.Y > rect1End.Y+1 || rect2End.Y < rect1Start.Y-1);         
    return result;
}

#endif
