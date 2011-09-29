#pragma once

#ifndef MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_
#define MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_

#include <vector>
#include <exception>

#include "MapView.h"
#include "Point.h"
#include "EdgeInfo.h"
#include "FastVector.h"
#include "NavigationRectangle.h"

namespace AStar
{

template<class CellType, typename CoordType = float>
class NavRectMapView: 
	public MapView<Point<CoordType>, CellType, float>
{
private:	
        NavRectMapView();
protected:
    NavigationRectangle<CoordType, CellType, float> _global;
    std::vector<NavigationRectangle<CoordType, CellType, float>*> _navRects;

    inline NavigationRectangle<CoordType, CellType, float>* GetNavRect(int index)
    {
        return _navRects[index];
    }
    //AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors);
public:
	virtual void GetNeighbors(int node, FastVector<EdgeInfo<int,float>>& neighbors);

	virtual Point<CoordType> GetPoint(int node);	
	virtual int GetNode(Point<CoordType>& point);
    virtual void SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size) 
    {
        throw new std::exception("Not implemented");
    }
	virtual Point<CoordType> GetMaxPoint()
    {
        throw new std::exception("Not implemented");
        //return null;
    }
    virtual int GetMaxNode()  
    { 
        return _map.size();//-1; 
    }
	virtual float GetCost(int nodeStart,int nodeGoal);
	virtual bool OnMap(Point<CoordType>& point)
    {
        return true;//_global.IsInside(point);
    }

    void ToOutput()
    {
        printf("Not implemented=(");
    }

    NavRectMapView(std::vector<Rectangle<CoordType>> rectangles, CoordType step);

	virtual ~NavRectMapView();

     
};

#include "NavRectMapView.inl"

}

#endif//MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_
