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

template<typename CoordType>
Rectangle<CoordType> Rectangle<CoordType>::
GetIntersection(Rectangle<CoordType>* rect, CoordType step)
{
    if ((rect == NULL)||(rect == this))
        return Rectangle<CoordType>();

    Point<CoordType> rect1Start = GetLeftTopPoint()-step;    
    Point<CoordType> rect1End = GetRightBottomPoint()+step;

    Point<CoordType> rect2Start = rect->GetLeftTopPoint()-step;
    Point<CoordType> rect2End = rect->GetRightBottomPoint()+step;

    bool isIntersect = !(rect2Start.X > rect1End.X || rect2End.X < rect1Start.X 
        || rect2Start.Y > rect1End.Y || rect2End.Y < rect1Start.Y); 
    if (isIntersect)
    {
        std::vector<CoordType> xarr(4);
        xarr[0] = rect1Start.X;
        xarr[1] = rect2Start.X;
        xarr[2] = rect1End.X;
        xarr[3] = rect2End.X;        
        std::sort(xarr.begin(), xarr.end());

        std::vector<CoordType> yarr(4);
        yarr[0] = rect1Start.Y;
        yarr[1] = rect2Start.Y;
        yarr[2] = rect1End.Y;
        yarr[3] = rect2End.Y;
        std::sort(yarr.begin(), yarr.end());
    
        Point<CoordType> lt(xarr[1], yarr[1]);
        Point<CoordType> rb(xarr[2], yarr[2]);
        Point<CoordType> size = rb - lt;
        if (size.X > 2*step)
        {
            lt.X += step;
            rb.X -= step;
        }
        if (size.Y > 2*step)
        {
            lt.Y += step;
            rb.Y -= step;
        }
        return Rectangle<CoordType>(lt,rb);
    }
    else
    {
        return Rectangle<CoordType>();
    }
    //return result;
}

template<typename CoordType>
bool Rectangle<CoordType>::
IsEmpty(CoordType stepSize)
{
    Point<CoordType> rect1Start = GetLeftTopPoint();
    Point<CoordType> rect1End = GetRightBottomPoint();
    return ((rect1Start.X+stepSize > rect1End.X) ||
        ((rect1Start.Y+stepSize > rect1End.Y)));
}

#endif
