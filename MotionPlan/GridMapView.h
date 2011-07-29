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
class GridMapView: 
	public AStar::MapView<Point, CellType, int, float>
{
public:
	//typedef int NodeInfo;
	//typedef float CostInfo;
	//typedef Point PointInfo;
	//typedef typename AStar::EdgeInfo<NodeInfo,CostInfo> Edge;
	
private:
	CellType* _map;
	int _width;
	int _height;
	int _border;
	std::vector<AStar::EdgeInfo<int,float>> _neighbors;
protected:
	void InitMap(int width, int height, int border);
	int GetBorder();
public:
	void GetNeighbors(int& node, std::vector<AStar::EdgeInfo<int,float>>& neighbors);
	Point GetPoint(int& node);	
	int GetNode(Point& point);
	CellType GetCell(int& node);
	void SetCell(int& node, CellType cell);
	void SetCellRegion(Point& point, CellType cell, Point& size);
	Point GetMaxPoint();
	int GetMaxNode();
	float GetCostPoint(const Point& point1,const Point& point2);

	GridMapView(int width, int height);
	GridMapView(int width, int height, int border);

	~GridMapView();
	void Clear(CellType value, CellType valueBorder);
	void ToOutput();
	void ToOutputField();
	static GridMapView<int>* LoadFrom(std::string &data, std::vector<Point>* specialPoints);

};

#include "GridMapView.inl"

#endif//MOTIONPLAN_GRIDMAPVIEW_H_
