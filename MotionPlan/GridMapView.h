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

template<class CellType>
class GridMapView: public AStar::MapView<Point, CellType, int, float>
{
public:
	typedef int NodeInfo;
	typedef float CostInfo;
	typedef typename Point PointInfo;
	typedef typename AStar::EdgeInfo<NodeInfo,CostInfo> Edge;
	
private:
	CellType* _map;
	int _width;
	int _height;
	int _border;
	std::vector<Edge> _neighbors;
protected:
	void InitMap(int width, int height, int border);
	int GetBorder();
public:
	void GetNeighbors(NodeInfo& node, std::vector<Edge>& neighbors);
	PointInfo GetPoint(NodeInfo& node);	
	NodeInfo GetNode(PointInfo& point);
	CellType GetCell(NodeInfo& node);
	void SetCell(NodeInfo& index, CellType cell);
	void SetCellRegion(PointInfo& point, CellType cell, PointInfo& size);
	PointInfo GetMaxPoint();
	NodeInfo GetMaxNode();
	CostInfo GetCost(NodeInfo& node1, NodeInfo& node2);


	GridMapView(int width, int height);
	GridMapView(int width, int height, int border);

	~GridMapView();
	void ToOutput();
	void ToOutputField();
	static GridMapView<int>* LoadFrom(std::string &data, std::vector<Point>* specialPoints);

};

#include "GridMapView.inl"

#endif//MOTIONPLAN_GRIDMAPVIEW_H_
