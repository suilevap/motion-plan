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
#include "KDTree.h"


namespace AStar
{

template<class CellType, typename CoordType = float, bool UseAdditionalLinks = false>
class NavRectMapView: 
	public MapView<Point<CoordType>, CellType, float>
{
private:	

protected:
    Rectangle<CoordType> _global;
    CoordType _stepSize;
    std::vector<NavigationRectangle<CoordType, CellType, float>*> _navRects;
    KDTree<CoordType> _kdTree;

    int _areasCount;
    
    //use static method Create instead constructor
    NavRectMapView() {}
    void Init(std::vector<Rectangle<CoordType>> rectangles, CoordType step, CoordType minRectSize);
    inline void Init(std::vector<Rectangle<CoordType>> rectangles, CoordType step);

    int AddNavRect(Rectangle<CoordType> rect, CellType value);

    void LinkNavRect(NavigationRectangle<CoordType, CellType, float>* navRect1, NavigationRectangle<CoordType, CellType, float>* navrect2);
    void LinkNavRect(int navRectNode1, int navRectNode2);

public:
    inline int GetAreasCount()
    {
        return _areasCount;
    }
    inline bool IsArea(int node)
    {
        return (node > 0 && node < GetAreasCount());
    }
    inline NavigationRectangle<CoordType, CellType, float>* GetNavRect(int index)
    {
        return _navRects[index];
    }
	virtual void GetNeighbors(int node, FastVector<EdgeInfo<int,float>>& neighbors);
    virtual void GetPointNeighbors(Point<CoordType> point, FastVector<EdgeInfo<int,float>>& neighbors);

	virtual Point<CoordType> GetPoint(int node);	
	virtual int GetNode(Point<CoordType>& point);
    virtual void SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size) 
    {
        throw new std::exception("Not implemented");
    }
	virtual Point<CoordType> GetMaxPoint()
    {        
        return _global.GetRightBottomPoint();
    }
    virtual int GetMaxNode()  
    { 
        return _map.size();//-1; 
    }
	virtual float GetCost(Point<CoordType>& p1, Point<CoordType>& p2);
	virtual bool OnMap(Point<CoordType>& point)
    {
        return _global.IsInside(point);
    }

    virtual Path<Point<CoordType>>* AdjustPath(Path<Point<CoordType>>* path);


    void ToOutput();

    static NavRectMapView<CellType, CoordType>* CreateCustom(std::vector<Rectangle<CoordType>> rectangles, CoordType step);

	virtual ~NavRectMapView();

     
};

#include "NavRectMapView.inl"

}

#endif//MOTIONPLAN_ASTAR_NAVRECTMAPVIEW_H_
