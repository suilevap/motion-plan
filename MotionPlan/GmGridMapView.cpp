#include "stdafx.h"

#include "GmGridMapView.h"


void GmGridMapView::SetGmGridId(int gmGridIdBase, int gmGridIdCost) 
{ 
    _gmGridIdBase = gmGridIdBase; 
    _gmGridWidth = gm::ds_grid_width(_gmGridIdBase);
    _gmGridHeight = gm::ds_grid_height(_gmGridIdBase);
    _gmGridIdCost = gmGridIdCost;
}

double GmGridMapView::GetCellCost(int node)
{
    Point<int> p = GetPoint(node);
    double result = gm::ds_grid_get(_gmGridIdBase, p.X, p.Y);
    return result;
}
bool GmGridMapView::IsCellTraversable(int node)
{
    Point<int> p = GetPoint(node);
    bool result = (gm::ds_grid_get(_gmGridIdCost, p.X, p.Y) != 0);
    return result;
}

int GmGridMapView::GetNodeDxDy(int node, int dx, int dy)
{
    int result;
    int x = node % _gmGridWidth + dx;
    int y = node / _gmGridWidth + dy;
    if (OnMap(x, y))
    {
        result = x + y * _gmGridWidth;
    }
    else
    {
        result = node;
    }
    return result;
}

Point<int> GmGridMapView::GetPoint(int node)
{
    Point<int> pointMap;
    pointMap.X = node % _gmGridWidth;
    pointMap.Y = node / _gmGridWidth;
    return pointMap;        
}

int GmGridMapView::GetNode(Point<int>& point)
{
    return (point.X) + point.Y * _gmGridWidth ;    
}

void GmGridMapView::GetNeighbors(int node, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
{
    neighbors.clear();
    neighbors.resize(8);
    float cost = GetCellCost(node);
    float step1 = 1 * cost;
    float stepD = SQRT_2 * cost;
    AddNeighbor( GetNodeDxDy(node, 1, 0) , step1, neighbors);
    AddNeighbor( GetNodeDxDy(node, - 1, 0) , step1, neighbors);
    AddNeighbor( GetNodeDxDy(node, 0, 1) , step1, neighbors);
    AddNeighbor( GetNodeDxDy(node, 0, -1) , step1, neighbors);

    AddNeighbor( GetNodeDxDy(node, 1, 1), stepD, neighbors);
    AddNeighbor( GetNodeDxDy(node, 1, -1), stepD, neighbors);
    AddNeighbor( GetNodeDxDy(node, -1, 1), stepD, neighbors);
    AddNeighbor( GetNodeDxDy(node, -1, -1), stepD, neighbors);
	
}

void GmGridMapView::AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
{
    if (IsCellTraversable(node))	
    {
        neighbors.push_back(AStar::EdgeInfo<int,float>(node, d));
    }
}

Point<int> GmGridMapView::GetMaxPoint()
{
    return Point<int>(_gmGridWidth, _gmGridHeight);
}

int GmGridMapView::GetMaxNode()
{
    return _gmGridWidth * _gmGridHeight;
}

bool GmGridMapView::OnMap(Point<int>& point)
{
    Point<int> maxPoint = GetMaxPoint();
    return ((point.X >= 0) &&(point.Y >= 0)&&(point.X < maxPoint.X)&&(point.Y < maxPoint.Y));
}

bool GmGridMapView::OnMap(int x, int y)
{
    return (x>=0 && x<_gmGridWidth && y>=0 && y<_gmGridHeight );
}
