#ifndef MOTIONPLAN_ASTAR_NAVIGATIONRECTANGLE_H
#error "Include from NavigationRectangle.h only."
#else

#include "DistanceEvaluator.h"

template<
	typename CoordType, 
	typename CellType, 
	typename CostInfo> 
NavigationRectangle<CoordType, CellType, CostInfo>::
NavigationRectangle(Point<CoordType> point1, Point<CoordType> point2, int index, CellType value)
    :Rectangle<CoordType>(point1, point2)
{
    _index = index;
    _value = value;
}

template<
	typename CoordType, 
	typename CellType, 
	typename CostInfo> 
NavigationRectangle<CoordType, CellType, CostInfo>::
NavigationRectangle(Rectangle<CoordType>& rect, int index, CellType value)
    :Rectangle<CoordType>(rect.GetLeftTopPoint(), rect.GetRightBottomPoint())
{
    _index = index;
    _value = value;
}

template<
	typename CoordType, 
	typename CellType, 
	typename CostInfo> 
void NavigationRectangle<CoordType, CellType, CostInfo>::
AddEdge(EdgeInfo<int, CostInfo> edge)
{
    _links.push_back(edge);
}

template<
	typename CoordType, 
	typename CellType, 
	typename CostInfo> 
void NavigationRectangle<CoordType, CellType, CostInfo>::
FindNeighbors(std::vector<NavigationRectangle<CoordType, CellType, CostInfo>*> navRects, CoordType step)
{
    for (
        std::vector<NavigationRectangle<CoordType, CellType, CostInfo>*>::iterator 
        it = navRects.begin(); 
        it != navRects.end(); 
        ++it)
    {
        NavigationRectangle<CoordType, CellType, CostInfo>* navRect = *it;
        if (IsNeighbor(navRect, step))
        {
            CostInfo d = AStar::DistanceEvaluator::EuclideanDistance<CostInfo, CoordType>(
                GetCenter(), 
                navRect->GetCenter());

            _links.push_back(EdgeInfo<int, CostInfo>(navRect->GetId(),d));
        }
    }
}

#endif
