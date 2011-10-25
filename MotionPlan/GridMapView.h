#pragma once

#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#define MOTIONPLAN_GRIDMAPVIEW_H_

#include <vector>
#include "MapView.h"
#include "Point.h"
#include "EdgeInfo.h"
#include "FastVector.h"

#include <valarray>

template<class CellType, typename CoordType = float>
class GridMapView: 
	public AStar::MapView<Point<CoordType>, CellType, float>
{
private:
	//CellType* _map;
    
protected:
	int _width;
	int _height;
	int _border;

	Point<float> _scale;
	Point<CoordType> _cellSize;

    GridMapView<int, CoordType>* _distanceField;
    void CreateDistanceField();

	virtual void InitMap(CoordType width, CoordType height, int border, Point<CoordType> cellSize);
	int GetBorder();
	void TransformPointToCell(Point<CoordType>& pointFrom, Point<int>& pointTo);
	void TransformPointToWorld(Point<int>& pointFrom, Point<CoordType>& pointTo);

	Point<int> GetMapPoint(int node);
	int GetNodeFromMapPoint(const Point<int>& point);

	void AddNeighbor(int node, float d, FastVector<AStar::EdgeInfo<int,float>>& neighbors);
    int GetNodeDxDy(int node, int dx, int dy);

public:

    static const CellType ObstacleCellValue = 1;
    static const CellType FreeCellValue = 0;

	virtual void GetNeighbors(int node, FastVector<AStar::EdgeInfo<int,float>>& neighbors);

	virtual Point<CoordType> GetPoint(int node);	
	virtual int GetNode(Point<CoordType>& point);
	virtual void SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size);
	virtual Point<CoordType> GetMaxPoint();
	virtual int GetMaxNode();
	virtual float GetCost(Point<CoordType>& point1, Point<CoordType>& point2);
	virtual bool OnMap(Point<CoordType>& point);

	Point<CoordType>& GetCellSize() {return _cellSize;}

	GridMapView(CoordType width, CoordType height);
	GridMapView(CoordType width, CoordType height, CoordType cellWidth);
	GridMapView();

	//GridMapView(int width, int height, int border);
	//GridMapView(int width, int height, int border, f);


	virtual ~GridMapView();
	void Clear(CellType value, CellType valueBorder);
    bool IsCellRegionIsotropic(Point<CoordType>& point1, Point<CoordType>& point2, CellType* cell);
    GridMapView<int, CoordType>* GetDistanceField();
    //return width
	int ToVector(std::vector<CellType>* data);


	virtual void ToOutput();
	void ToOutputField();
	static GridMapView<int>* LoadFrom(std::string &data, std::vector<Point<CoordType>>* specialPoints);
	void LoadFromVector(std::vector<CoordType>& data);
	void ToOtputDebugStep();
};

#include "GridMapView.inl"

#endif//MOTIONPLAN_GRIDMAPVIEW_H_
