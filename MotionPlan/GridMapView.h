#pragma once

#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#define MOTIONPLAN_GRIDMAPVIEW_H_

#include <stack>
#include <vector>
#include <string>
#include "MapView.h"
#include "Point.h"
#include "DistanceEvaluator.h"


//typedef float CellType;

template<class CellType>
class GridMapView: AStar:: public MapView<Point, CellType, int, float>
{
	typedef int NodeInfo;
	typedef float CostInfo;
	typedef Point PointInfo;
	typedef Edge<NodeInfo,CostInfo> GridMapView::Edge;
	
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
	GridMapView(int width, int height);
	GridMapView(int width, int height, int border)

	~GridMapView();
	void ToOutput();
	void ToOutputField();
	static Map<int>* LoadFrom(std::string &data, std::vector<Point>* specialPoints);

};

#include "GridMapView.inl"

#endif//MOTIONPLAN_GRIDMAPVIEW_H_
