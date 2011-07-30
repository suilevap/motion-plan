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

template<class CellType, typename CoordType = float>
class GridMapView: 
	public AStar::MapView<Point<CoordType>, CellType, int, float>
{
private:
	CellType* _map;
	int _width;
	int _height;
	int _border;

	float _scaleX;
	float _scaleY;
	float _scaleXReverse;
	float _scaleYReverse;
	
protected:
	void InitMap(int width, int height, int border, float scaleX, float scaleY);
	int GetBorder();
	void TransformPoint(Point<CoordType>& point, Point<int>& p);
	void TransformPointReverse(Point<CoordType>& point, Point<int>& p);

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
	GridMapView(int width, int height, float scaleX, float scaleY);

	//GridMapView(int width, int height, int border);
	//GridMapView(int width, int height, int border, f);


	virtual ~GridMapView();
	void Clear(CellType value, CellType valueBorder);
	void ToOutput();
	void ToOutputField();
	static GridMapView<int>* LoadFrom(std::string &data, std::vector<Point<CoordType>>* specialPoints);

};

#include "GridMapView.inl"

#endif//MOTIONPLAN_GRIDMAPVIEW_H_
