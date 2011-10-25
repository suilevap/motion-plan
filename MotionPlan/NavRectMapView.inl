#ifndef MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_
#error "Include from NavRectMapView.h only."
#else

#include "DistanceEvaluator.h"
#include "MathConstants.h"

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>:: 
GetNeighbors(int node, FastVector<EdgeInfo<int,float>>& neighbors)
{
	NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(node);
    neighbors.set(navRect->GetNeighboors());    
}

//template<class CellType, typename CoordType, bool UseAdditionalLinks>
//inline void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
//{
//    //if (GetCell(node) != 1)	
//    {
//        neighbors.push_back(AStar::EdgeInfo<int,float>(node, d));
//    }
//}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
Point<CoordType> NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
GetPoint(int node)
{
    return GetNavRect(node)->GetCenter();
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
int NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
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

template<class CellType, typename CoordType, bool UseAdditionalLinks>
float NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
GetCost(Point<CoordType>& p1,Point<CoordType>& p2)
{
	float cost = AStar::DistanceEvaluator::EuclideanDistance<float>(p1, p2);
    return cost;
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
NavRectMapView<CellType, CoordType>* NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
CreateCustom(std::vector<Rectangle<CoordType>> rectangles, CoordType step)
{
    NavRectMapView<CellType, CoordType>* result = new NavRectMapView<CellType, CoordType>();
    result->Init(rectangles, step);
    return result;
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
Init(std::vector<Rectangle<CoordType>> rectangles, CoordType step)
{    
    if (rectangles.size() == 0)
        return;
    _stepSize = step;

    Point<CoordType> minP = rectangles[0].GetLeftTopPoint();
    Point<CoordType> maxP = rectangles[0].GetRightBottomPoint();
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

        //TODO: need refactoring
        minP.X = min(minP.X, it->GetLeftTopPoint().X);
        minP.Y = min(minP.Y, it->GetLeftTopPoint().Y);

        maxP.X = max(maxP.X, it->GetRightBottomPoint().X);
        maxP.Y = max(maxP.Y, it->GetRightBottomPoint().Y);
    }
    _map.resize(_navRects.size());

    //TODO: implement smth clever than that simple brut force
    int count = GetMaxNode();
    for (int i = 1; i < count; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        navRect->FindNeighbors(_navRects, _stepSize);
    }

    _global = Rectangle<CoordType>(minP, maxP);
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
NavRectMapView<CellType, CoordType, UseAdditionalLinks>::~NavRectMapView()
{
    int count = GetMaxNode();
    for (int i = 1; i < count; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        delete navRect;
    }
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
ToOutput()
{
    Point<CoordType> startPoint = _global.GetLeftTopPoint();
    Point<CoordType> endPoint = _global.GetRightBottomPoint();
    Point<CoordType> curPoint;

	CoordType w = endPoint.X;
	CoordType h = endPoint.Y;
	for (CoordType k = startPoint.Y + _stepSize /2; k <= h; k += _stepSize)
	{
		for (CoordType i = startPoint.X + _stepSize /2; i <= w; i += _stepSize)
		{
			//printf("%3d",(int)( (int)(GetCell(i , k)*10 )%100 ));
			Point<CoordType> point(i , k);
			printf("%2d",GetNode(point));
		}
		printf("\n");
	}
	printf("========================\n");
}

#endif
