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
bool Rectangle<CoordType>::
IsIntersect(Rectangle<CoordType>* navRect)
{
    if ((navRect == NULL)||(navRect == this))
        return false;

    bool result = false;
    Point<CoordType> rect1Start = GetLeftTopPoint();
    Point<CoordType> rect2Start = navRect->GetLeftTopPoint();
    Point<CoordType> rect1End = GetRightBottomPoint();
    Point<CoordType> rect2End = navRect->GetRightBottomPoint();
    result = !(rect2Start.X >= rect1End.X || rect2End.X <= rect1Start.X 
        || rect2Start.Y >= rect1End.Y || rect2End.Y <= rect1Start.Y); 

    return result;
}

template<typename CoordType>
Rectangle<CoordType> Rectangle<CoordType>::
GetIntersection(Rectangle<CoordType>* rect, CoordType step)
{
    if ((rect == NULL)||(rect == this))
        return Rectangle<CoordType>();

    Point<CoordType> rect1Start = GetLeftTopPoint()-step*0;    
    Point<CoordType> rect1End = GetRightBottomPoint()+step*0;

    Point<CoordType> rect2Start = rect->GetLeftTopPoint()-step*0;
    Point<CoordType> rect2End = rect->GetRightBottomPoint()+step*0;

    bool isIntersect = !(rect2Start.X > rect1End.X+step || rect2End.X+step < rect1Start.X 
        || rect2Start.Y > rect1End.Y+step || rect2End.Y+step < rect1Start.Y); 
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
        if (size.X > step)
        {
            lt.X += step/2;
            rb.X -= step/2;
        }
        if (size.Y > step)
        {
            lt.Y += step/2;
            rb.Y -= step/2;
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

template<typename CoordType>
Rectangle<CoordType> Rectangle<CoordType>::
GetUnion(Rectangle<CoordType>* rect)
{
    Point<CoordType> lt;
    Point<CoordType> rb;
    Point<CoordType> size1 = GetSize();
    Point<CoordType> size2 = rect->GetSize();

    if (size1.X==0 && size1.Y==0)
    {
        lt = rect->GetLeftTopPoint();
        rb = rect->GetRightBottomPoint();
    }
    else if (size2.X==0 && size2.Y==0)
    {
        lt = GetLeftTopPoint();
        rb = GetRightBottomPoint();
    }
    else
    {
        lt = Point<CoordType>(
            min(GetLeftTopPoint().X, rect->GetLeftTopPoint().X),
            min(GetLeftTopPoint().Y, rect->GetLeftTopPoint().Y));
        rb = Point<CoordType>(
            max(GetRightBottomPoint().X, rect->GetRightBottomPoint().X),
            max(GetRightBottomPoint().Y, rect->GetRightBottomPoint().Y));
    }
    Rectangle<CoordType> result(lt,rb);
    return result;
}


#endif
