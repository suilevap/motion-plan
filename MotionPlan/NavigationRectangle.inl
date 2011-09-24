#ifndef MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
#error "Include from NavigationRectangle.h only."
#else

#include "DistanceEvaluator.h"

template<
	typename PointT, 
	typename CellType, 
	typename CostInfo> 
NavigationRectangle<PointT, CellType, CostInfo>::
NavigationRectangle(Point<PointT> point1, Point<PointT> point2, int index, CellType value)
    :Rectangle<PointT>(point1, point2)
{
    _index = index;
    _value = value;
}

template<
	typename PointT, 
	typename CellType, 
	typename CostInfo> 
NavigationRectangle<PointT, CellType, CostInfo>::
NavigationRectangle(Rectangle<PointT>& rect, int index, CellType value)
    :Rectangle<PointT>(rect.LefTopPoint, rect.RightBottomPoint)
{
    _index = index;
    _value = value;
}

template<
	typename PointT, 
	typename CellType, 
	typename CostInfo> 
void NavigationRectangle<PointT, CellType, CostInfo>::
FindNeighbors(std::vector<NavigationRectangle<PointT, CellType, CostInfo>*> navRects)
{
    for (
        std::vector<NavigationRectangle<PointT, CellType, CostInfo>*>::iterator 
        it = navRects.begin(); 
        it != navRects.end(); 
        ++it)
    {
        if (IsNeighbor(*it))
        {
            CostInfo d = DistanceEvaluator::EuclideanDistance<CostInfo, PointT>(
                GetCenter(), 
                it->GetCenter());

            _links.pushk_back(EdgeInfo<int, CostInfo>(it->GetId(),d));
        }
    }
}

#endif
