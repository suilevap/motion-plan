#pragma once

#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#define MOTIONPLAN_GRIDMAPVIEW_H_

#include <stack>
#include <vector>
#include <string>
#include "MapView.h"
#include "Point.h"
#include "EdgeInfo.h"
#include "DistanceEvaluator.h"


//typedef float CellType;

template<class CellType, typename CoordType = int>
class GridMapView: 
	public AStar::MapView<Point<CoordType>, CellType, int, float>
{
public:
	//typedef Point<CoordType> Point;
	//typedef int NodeInfo;
	//typedef float CostInfo;
	//typedef Point PointInfo;
	//typedef typename AStar::EdgeInfo<NodeInfo,CostInfo> Edge;
	
private:
	CellType* _map;
	int _width;
	int _height;
	int _border;
	//std::vector<AStar::EdgeInfo<int,float>> _neighbors;
protected:
	void InitMap(int width, int height, int border);
	int GetBorder();
public:
	virtual void GetNeighbors(int& node, std::vector<AStar::EdgeInfo<int,float>>& neighbors);
	virtual Point<CoordType> GetPoint(int& node);	
	virtual int GetNode(Point<CoordType>& point);
	virtual CellType GetCell(int& node);
	virtual void SetCell(int& node, CellType cell);
	virtual void SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size);
	virtual Point<CoordType> GetMaxPoint();
	virtual int GetMaxNode();
	virtual float GetCostPoint(const Point<CoordType>& point1, const Point<CoordType>& point2);

	GridMapView(int width, int height);
	GridMapView(int width, int height, int border);

	virtual ~GridMapView();
	void Clear(CellType value, CellType valueBorder);
	void ToOutput();
	void ToOutputField();
	static GridMapView<int>* LoadFrom(std::string &data, std::vector<Point<CoordType>>* specialPoints);

};

#include "GridMapView.inl"

#endif//MOTIONPLAN_GRIDMAPVIEW_H_
