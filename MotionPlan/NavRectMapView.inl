#ifndef MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_
#error "Include from NavRectMapView.h only."
#else

#include "DistanceEvaluator.h"
#include "MathConstants.h"

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>:: 
GetNeighbors(int node, FastVector<EdgeInfo<int,float>>& neighbors)
{
    if (UseAdditionalLinks && IsArea(node))
    {
        //area node can be part of optimal path and can be final point
        neighbors.clear();    
    }
    else
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(node);
        neighbors.set(navRect->GetNeighboors());    
    }
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>:: 
GetPointNeighbors(Point<CoordType> point, FastVector<EdgeInfo<int,float>>& neighbors)
{
    
    int node = GetNode(point);
    
    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(node);
    std::vector<EdgeInfo<int, float>>* neighborsNode = navRect->GetNeighboors();   

    int count = neighborsNode->size();
    neighbors.resize(count+1);
    neighbors.clear();

    for (int i = 0; i < count; ++i)
    {
        EdgeInfo<int,float>& edge = (*neighborsNode)[i];
        float cost = GetCost(point, GetNavRect(edge.To)->GetCenter());
        neighbors.push_back(EdgeInfo<int,float>(edge.To, cost));
    }    
    //add area node
    float cost = GetCost(point, GetNavRect(node)->GetCenter());
    neighbors.push_back(EdgeInfo<int,float>(node, cost));
}

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
    //TODO: implement smth clever than that simple brut force (for example KD-tree)   
    int count = _areasCount;
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
int NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
AddNavRect(Rectangle<CoordType> rect, CellType value)
{
    int index = _navRects.size();
    _navRects.push_back( 
        new NavigationRectangle<CoordType, CellType, float>(rect, index, value)); 
    return index;
}

//TODO: need refactoring
template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
Init(std::vector<Rectangle<CoordType>> rectangles, CoordType step)
{    
    if (rectangles.size() == 0)
        return;
    _stepSize = step;

    Point<CoordType> minP = rectangles[0].GetLeftTopPoint();
    Point<CoordType> maxP = rectangles[0].GetRightBottomPoint();

    _navRects.push_back(NULL);

    for (std::vector<Rectangle<CoordType>>::iterator it = rectangles.begin(); 
        it != rectangles.end(); 
        ++it)
    {
        AddNavRect(*it, 0);    

        //TODO: need refactoring
        minP.X = min(minP.X, it->GetLeftTopPoint().X);
        minP.Y = min(minP.Y, it->GetLeftTopPoint().Y);

        maxP.X = max(maxP.X, it->GetRightBottomPoint().X);
        maxP.Y = max(maxP.Y, it->GetRightBottomPoint().Y);
    }
    _areasCount = _navRects.size();

    //TODO: implement smth clever than that simple brut force
    int count = _areasCount;
    for (int i = 1; i < count; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        
        //navRect->FindNeighbors(_navRects, _stepSize);

        for (int k = i+1; k < count; ++k)
        {
            NavigationRectangle<CoordType, CellType, float>* navRect2 = GetNavRect(k);
            if (navRect->IsNeighbor(navRect2, _stepSize))
            {
                if (!UseAdditionalLinks)
                {
                    float d = GetCost(navRect->GetCenter(), navRect2->GetCenter());
                    navRect->AddEdge(EdgeInfo<int, float>(navRect2->GetId(),d));
                    //symmetric
                    navRect2->AddEdge(EdgeInfo<int, float>(navRect->GetId(),d));
                }
                else
                {                
                    Rectangle<CoordType> intesetionRect = navRect->GetIntersection(navRect2, _stepSize);

                    int index = AddNavRect(intesetionRect, 0);
                    NavigationRectangle<CoordType, CellType, float>* endgeNavRect = GetNavRect(index);

                    float d1 = GetCost(navRect->GetCenter(), endgeNavRect->GetCenter());
                    navRect->AddEdge(EdgeInfo<int, float>(endgeNavRect->GetId(),d1));
                    endgeNavRect->AddEdge(EdgeInfo<int, float>(navRect->GetId(),d1));

                    //symmetric                    
                    Rectangle<CoordType> intesetionRect2 = navRect2->GetIntersection(navRect, _stepSize);
                    int index2 = AddNavRect(intesetionRect2, 0);
                    NavigationRectangle<CoordType, CellType, float>* endgeNavRect2 = GetNavRect(index2);

                    float d2 = GetCost(navRect2->GetCenter(), endgeNavRect2->GetCenter());
                    navRect2->AddEdge(EdgeInfo<int, float>(endgeNavRect2->GetId(),d2)); 
                    endgeNavRect2->AddEdge(EdgeInfo<int, float>(navRect2->GetId(),d2));

                    //link between edge nodes
                    float dEdges = GetCost(endgeNavRect->GetCenter(), endgeNavRect2->GetCenter());
                    endgeNavRect->AddEdge(EdgeInfo<int, float>(endgeNavRect2->GetId(),dEdges)); 
                    endgeNavRect2->AddEdge(EdgeInfo<int, float>(endgeNavRect->GetId(),dEdges)); 

                }
                /*float d = GetCost(GetCenter(), navRect->GetCenter());
                _links.push_back(EdgeInfo<int, float>(navRect->GetId(),d));*/
            }
        }
        if (UseAdditionalLinks)
        {
            //link all portal of
            std::vector<EdgeInfo<int, float>>* edges = navRect->GetNeighboors();
            int edgesCount = edges->size();
            for (int k1 = 0; k1 < edgesCount; ++k1 )
            {
                int edgeIndex1 = edges->at(k1).To;
                NavigationRectangle<CoordType, CellType, float>* navRectEdge1 = GetNavRect(edgeIndex1);
                for (int k2 = k1+1; k2 < edgesCount; ++k2 )
                {
                    int edgeIndex2 = edges->at(k2).To;
                    NavigationRectangle<CoordType, CellType, float>* navRectEdge2 = GetNavRect(edgeIndex2);
                    float d = GetCost(navRectEdge1->GetCenter(), navRectEdge2->GetCenter());
                    navRectEdge1->AddEdge(EdgeInfo<int, float>(navRectEdge2->GetId(),d)); 
                    //symmetric
                    navRectEdge2->AddEdge(EdgeInfo<int, float>(navRectEdge1->GetId(),d)); 

                }
            }
        }
    }
    _map.resize(_navRects.size());

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
