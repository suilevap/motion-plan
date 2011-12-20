#pragma once
#ifndef MOTIONPLAN_GMGRIDMAPVIEW_H_
#define MOTIONPLAN_GMGRIDMAPVIEW_H_

#ifdef USE_GMAPI
#define GMAPI_NO_D3D
#include "gmapi.h"
#endif
#include "MapView.h"
#include <vector>
#include "FastVector.h"
#include "Point.h"
#include "EdgeInfo.h"
#include "DistanceEvaluator.h"

class GmGridMapView :
	public AStar::MapView<Point<int>, float, float>
{
protected:
	int _gmGridIdBase;
    int _gmGridIdCost;
    int _gmGridWidth;
    int _gmGridHeight;
    int _cellSize;
    float _cellSCale;

    inline double GetCellCost(int node);
    inline bool IsCellTraversable(int node);
    
    inline int GetNodeDxDy(int node, int dx, int dy);
    inline void AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors);
    inline bool OnMap(int x, int y);
public:
    void SetGmGridId(int gmGridIdBase, int gmGridIdCost);

	virtual Point<int> GetPoint(int node);
	virtual int GetNode(Point<int>& point);

	virtual void GetNeighbors(int node, FastVector<AStar::EdgeInfo<int,float>>& neighbors);      

	virtual Point<int> GetMaxPoint();
	virtual int GetMaxNode();
    virtual bool OnMap(Point<int>& point);

    virtual void SetCellRegion(Point<int>& point, float cell, Point<int>& size)
    {
    }

    virtual void ToOutput()
    {
    }

    GmGridMapView()
    {
    }
    virtual ~GmGridMapView(void) 
    {
    }

};

#endif//MOTIONPLAN_GMGRIDMAPVIEW_H_
