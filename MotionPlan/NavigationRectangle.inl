#ifndef MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
#error "Include from NavigationRectangle.h only."
#else

template<
	typename PointInfo, 
	typename CellType, 
	typename CostInfo> 
NavigationRectangle<PointInfo, CellType, CostInfo>::
NavigationRectangle(PointInfo point1, PointInfo point2)
{
	_leftTopPoint = point1;
	_rightBottomPoint = point2;
}

template<
	typename PointInfo, 
	typename CellType, 
	typename CostInfo> 
bool NavigationRectangle<PointInfo, CellType, CostInfo>::
IsNeighbor(NavigationRectangle<PointInfo, CellType, CostInfo>* navRect)
{
    bool result = false;
    PointInfo rect1Start = GetLeftTopPoint();
    PointInfo rect2Start = navRect->GetLeftTopPoint();
    PointInfo rect1End = GetRightBottomPoint();
    PointInfo rect2End = navRect->GetRightBottomPoint();
    result = !(rect2Start.X > rect1End.X+1 || rect2End.X < rect1Start.X-1 
        || rect2Start.Y > rect1End.Y+1 || rect2End.Y < rect1Start.Y-1);         
    return result;
}

template<
	typename PointInfo, 
	typename CellType, 
	typename CostInfo> 
void NavigationRectangle<PointInfo, CellType, CostInfo>::
FindNeighbors(std::vector<NavigationRectangle<PointInfo, CellType, CostInfo>*> navRects)
{
    for (std::vector<NavigationRectangle<PointInfo, CellType, CostInfo>*>::iterator it = navRects.begin(); it != navRects.end(); ++it)
    {
        if (IsNeighbor(*it))
        {
            CostInfo d = 0;
            _links.pushk_back(EdgeInfo<int, CostInfo>(it->GetId(),d));
        }
    }
}



#endif