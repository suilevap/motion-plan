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
    result = _kdTree.GetId(point);
    if (result<0)
    {
        result = 0;
    }
    ////TODO: implement smth clever than that simple brut force (for example KD-tree)   
    //int count = _areasCount;
    //for (int i = 1; i < count; ++i)
    //{
	   // NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
    //    if (navRect->IsInside(point))
    //    {
    //        result = i;
    //        break;
    //    }
    //}
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

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
LinkNavRect(int navRectNode1, int navRectNode2)
{
    LinkNavRect(GetNavRect(navRectNode1), GetNavRect(navRectNode2));
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
LinkNavRect(NavigationRectangle<CoordType, CellType, float>* navRect1, 
            NavigationRectangle<CoordType, CellType, float>* navRect2)
{
    float d = GetCost(navRect1->GetCenter(), navRect2->GetCenter());
    navRect1->AddEdge(EdgeInfo<int, float>(navRect2->GetId(),d));
    //symmetric
    navRect2->AddEdge(EdgeInfo<int, float>(navRect1->GetId(),d));
}

template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
Init(std::vector<Rectangle<CoordType>> rectangles, CoordType step)
{
    Init(rectangles, step, step);
}

//TODO: need refactoring
template<class CellType, typename CoordType, bool UseAdditionalLinks>
void NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
Init(std::vector<Rectangle<CoordType>> rectangles, CoordType step, CoordType minRectSize)
{    

    if (rectangles.size() == 0)
        return;
    _stepSize = step;

    //Point<CoordType> minP = rectangles[0].GetLeftTopPoint();
    //Point<CoordType> maxP = rectangles[0].GetRightBottomPoint();

    _navRects.push_back(NULL);

    std::vector<Rectangle<CoordType>> navRectsSmall;

    for (std::vector<Rectangle<CoordType>>::iterator it = rectangles.begin(); 
        it != rectangles.end(); 
        ++it)
    {

        Point<CoordType> size = it->GetSize();
        if (size.X >= minRectSize && size.Y >= minRectSize)
        {
            int id = AddNavRect(*it, 0); 
            _kdTree.Add(*it, id);
        }
        else
        {
            navRectsSmall.push_back(*it); 
        }
        _global = _global.GetUnion(&(*it));
    }
    _areasCount = _navRects.size();
    _kdTree.Build(minRectSize);

    //TODO: implement smth clever than that simple brut force
    int count = _areasCount;

    //add weak links (from small rects)
    int countSmall = navRectsSmall.size();
    for (int i = 0; i < countSmall; ++i)
    {
        Rectangle<CoordType> rect = navRectsSmall[i];
        std::vector<int> possibleNeighbors;
        for (int k = 1; k < _areasCount; ++k)
        {
            NavigationRectangle<CoordType, CellType, float>* navRect2 = GetNavRect(k);
            if (rect.IsNeighbor(navRect2, _stepSize))
            {
                possibleNeighbors.push_back(k);
            }
        }
        //not a leaf
        //HACK: optimization for small rects
        if (possibleNeighbors.size()>1)
        {
            int index = AddNavRect(rect, 0);
            NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(index);        
               
            count = possibleNeighbors.size();
            for (int k = 0; k < count; ++k)
            {
                int index = possibleNeighbors[k];
                NavigationRectangle<CoordType, CellType, float>* navRect2 = GetNavRect(index);
              
                if (!UseAdditionalLinks)
                {
                    LinkNavRect(navRect, navRect2);
                }
                else
                {                
                    Rectangle<CoordType> intesetionRect = navRect->GetIntersection(navRect2, minRectSize);

                    int index = AddNavRect(intesetionRect, 0);
                    NavigationRectangle<CoordType, CellType, float>* endgeNavRect = GetNavRect(index);          
                    LinkNavRect(navRect, endgeNavRect);
                    LinkNavRect(navRect2, endgeNavRect);
                }
            }
        }
    }

    //add strong link
    for (int i = 1; i < _areasCount; ++i)
    {
	    NavigationRectangle<CoordType, CellType, float>* navRect = GetNavRect(i);
        
        for (int k = i+1; k < _areasCount; ++k)
        {
            NavigationRectangle<CoordType, CellType, float>* navRect2 = GetNavRect(k);
            if (navRect->IsNeighbor(navRect2, _stepSize))
            {
                if (!UseAdditionalLinks)
                {
                    LinkNavRect(navRect, navRect2);
                }
                else
                {                
                    Rectangle<CoordType> intesetionRect = navRect->GetIntersection(navRect2, minRectSize);

                    int index = AddNavRect(intesetionRect, 0);
                    NavigationRectangle<CoordType, CellType, float>* endgeNavRect = GetNavRect(index);          
                    LinkNavRect(navRect, endgeNavRect);
                    LinkNavRect(navRect2, endgeNavRect);
                }
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
                    LinkNavRect(navRectEdge1, navRectEdge2);

                }
            }
        }
    }
    _map.resize(_navRects.size());

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
Path<Point<CoordType>>* NavRectMapView<CellType, CoordType, UseAdditionalLinks>::
AdjustPath(Path<Point<CoordType>>* path)
{
    int count = path->Count();
    //2 points is straight line
    if (count <= 2)
        return path;

    Path<Point<CoordType>>* result = new Path<Point<CoordType>>();
    result->Add(path->GetPoint(0), path->GetNode(0));

    Point<CoordType> portalApex = path->GetPoint(0);
    Point<CoordType> portalRight = path->GetPoint(0);
    Point<CoordType> portalLeft = path->GetPoint(0);
    Point<CoordType> point = path->GetPoint(0);
    int portalApexIndex = 0;
    int portalLeftIndex = portalApexIndex;
    int portalRightIndex = portalApexIndex;

    int i = 1;
    //for (int i = 1; i < count; ++i)
    while (i < count)
    {
        //right
        if (i != portalRightIndex)
        {
            int node = path->GetNode(i);
            if (node>0)
            {
                point = GetNavRect(node)->GetRightRot(portalRight);
            }
            else
            {
                point = path->GetPoint(i);
            }

            if (point.TriArea(portalApex, portalRight) >= 0.0f)
            {
                if ((portalRightIndex == portalApexIndex) || (point.TriArea(portalApex, portalLeft)<0.0f))
                {
                    portalRight = point;
                    portalRightIndex = i;
                }
                else
                {
                    portalApex = portalLeft;
                    portalApexIndex = portalLeftIndex;

                    result->Add(portalApex, path->GetNode(portalApexIndex));

                    portalLeft = portalApex;
                    portalLeftIndex = portalApexIndex;
                    portalRight = portalApex;
                    portalRightIndex = portalApexIndex;
                    
                    //restart
                    i = portalApexIndex;
                }
            }
        }

        //left
        if (i != portalLeftIndex)
        {
            int node = path->GetNode(i);
            if (node>0)
            {
                point = GetNavRect(node)->GetLeftRot(portalLeft);
            }
            else
            {
                point = path->GetPoint(i);
            }

            if (point.TriArea(portalApex, portalLeft) <= 0.0f)
            {
                if ((portalLeftIndex == portalApexIndex) || (point.TriArea(portalApex, portalRight)>0.0f))
                {
                    portalLeft = point;
                    portalLeftIndex = i;
                }
                else
                {
                    portalApex = portalRight;
                    portalApexIndex = portalRightIndex;

                    result->Add(portalApex, path->GetNode(portalApexIndex));

                    portalLeft = portalApex;
                    portalLeftIndex = portalApexIndex;
                    portalRight = portalApex;
                    portalRightIndex = portalApexIndex;
                    
                    //restart
                    i = portalApexIndex;
                }
            }
        }
        i++;
    }
    result->Add(path->GetPoint(count-1), path->GetNode(count-1));

    return result;
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
