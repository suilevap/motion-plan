#ifndef MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_
#error "Include from NavRectMapView.h only."
#else

#include "DistanceEvaluator.h"
#include "MathConstants.h"

template<class CellType, typename CoordType>
void NavRectMapView<CellType, CoordType>:: 
GetNeighbors(int node, FastVector<EdgeInfo<int,float>>& neighbors)
{
	NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(node);
    neighbors.set(navRect->GetNeighboors());    
}

//template<class CellType, typename CoordType>
//inline void NavRectMapView<CellType, CoordType>::AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
//{
//    //if (GetCell(node) != 1)	
//    {
//        neighbors.push_back(AStar::EdgeInfo<int,float>(node, d));
//    }
//}

template<class CellType, typename CoordType>
Point<CoordType> NavRectMapView<CellType, CoordType>::
GetPoint(int node)
{
    return GetNavRect(node)->GetCenter();
}

template<class CellType, typename CoordType>
int NavRectMapView<CellType, CoordType>::
GetNode(Point<CoordType>& point)
{
    int result = 0;
    //TODO: implement smth clever than that simple brut force    
    int count = GetMaxNode();
    for (int i = 1; i < count; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        if (navRect->IsInside(point))
        {
            result = i;
            break;
        }
    }
    return result;
}

template<class CellType, typename CoordType>
float NavRectMapView<CellType, CoordType>::
GetCost(int nodeStart,int nodeGoal)
{
    Point<int> p1 = GetPoint(nodeStart);
	Point<int> p2 = GetPoint(nodeGoal);
	float cost = AStar::DistanceEvaluator::EuclideanDistance<float>(p1, p2);
    return cost;
}

template<class CellType, typename CoordType>
NavRectMapView<CellType, CoordType>::
NavRectMapView()
{
}
    
template<class CellType, typename CoordType>
NavRectMapView<CellType, CoordType>::
NavRectMapView(std::vector<Rectangle<CoordType>> rectangles)
{    
    //Point<CoordType> minP(0,0);
    //Pont<CoordType> maxP(0,0);
    //_navRects.push_back(
    //    new NavigationRectangle<CoordType, CellType, float>(
    //        Point<CoordType>(0,0),Point<CoordType>(0,0), 0, 0));

    _navRects.push_back(NULL);

    for (std::vector<Rectangle<CoordType>>::iterator it = rectangles.begin(); 
        it != rectangles.end(); 
        ++it)
    {
        int index = _navRects.size();
        _navRects.push_back( 
            new NavigationRectangle<CoordType, CellType, float>(*it, index, 1));    
    }
    _map.resize(_navRects.size());

    //TODO: implement smth clever than that simple brut force
    int count = GetMaxNode();
    for (int i = 1; i < count; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        navRect->FindNeighbors(_navRects);
    }
}

template<class CellType, typename CoordType>
NavRectMapView<CellType, CoordType>::~NavRectMapView()
{
    int count = GetMaxNode();
    for (int i = 1; i < count; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        delete navRect;
    }
}

#endif
