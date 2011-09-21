#pragma once
#ifndef MOTIONPLAN_HEXGRIDMAPVIEW_H_
#define MOTIONPLAN_HEXGRIDMAPVIEW_H_

#include "GridMapView.h"
#include <vector>
#include "FastVector.h"
#include "Point.h"
#include "EdgeInfo.h"
#include "DistanceEvaluator.h"
//     _
// 0\ /2\_
// _/1\_/3\
// 4\_/6\_/
// _/5\_/7\
// 8\_/1\_/
// _/9\0/11
template<class CellType>
class HexGridMapView :
	public GridMapView<CellType, float>
{
protected:
	int GetYOffset(int node);
	int GetYOffset(const Point<float>& point);
public:
	HexGridMapView(float width, float height, float cellSize);
    virtual ~HexGridMapView(void) {};

	virtual void GetNeighbors(int node, FastVector<AStar::EdgeInfo<int,float>>& neighbors);
	virtual Point<float> GetPoint(int node);	
	virtual int GetNode(Point<float>& point);
	virtual float GetCost(int nodeStart,int nodeGoal);

	virtual void ToOutput();
};

#include "HexGridMapView.inl"

#endif//MOTIONPLAN_HEXGRIDMAPVIEW_H_
