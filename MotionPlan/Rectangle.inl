#ifndef MOTIONPLAN_ASTAR_RECTANGLE_H
#error "Include from Rectangle.h only."
#else

template<typename CoordType>
Rectangle<CoordType>::
Rectangle(Point<CoordType> point1, Point<CoordType> point2)
{
	_leftTopPoint = point1;
	_rightBottomPoint = point2;
    _center = Point<CoordType>::Avg(point1, point2);
}

template<typename CoordType>
bool Rectangle<CoordType>::
IsInside(const Point<CoordType>& point)
{
    return (point.X >= _leftTopPoint.X && point.Y >= _leftTopPoint.Y 
        && point.X <= _rightBottomPoint.X && point.Y <= _rightBottomPoint.Y);
}

template<typename CoordType>
bool Rectangle<CoordType>::
IsNeighbor(Rectangle<CoordType>* navRect, CoordType step)
{
    if ((navRect == NULL)||(navRect == this))
        return false;

    bool result = false;
    Point<CoordType> rect1Start = GetLeftTopPoint();
    Point<CoordType> rect2Start = navRect->GetLeftTopPoint();
    Point<CoordType> rect1End = GetRightBottomPoint();
    Point<CoordType> rect2End = navRect->GetRightBottomPoint();
    result = !(rect2Start.X > rect1End.X+step || rect2End.X+step < rect1Start.X 
        || rect2Start.Y > rect1End.Y+step || rect2End.Y+step < rect1Start.Y); 

    return result;
}

#endif
