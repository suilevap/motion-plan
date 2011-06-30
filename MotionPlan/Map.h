#pragma once

#ifndef MOTIONPLAN_MAP_H_
#define MOTIONPLAN_MAP_H_

#include <stack>
#include <vector>
#include <string>
#include "Point.h"
#include "DistanceEvaluator.h"


//typedef float CellType;

template<class CellType>
class Map
{
private:
	CellType* _map;
	int _width;
	int _height;
	int _border;

protected:
	void InitMap(int width, int height, int border);
	int GetBorder();
public:
	Map(int width, int height);
	Map(int width, int height, int border);
	template<class T>
	Map(Map<T>* map);
	~Map(void);

	Point GetCellPoint(int index);
	void GetD(int index1, int index2, int* dx, int* dy);
	float GetEvclDist(int p1, int p2);
	virtual int GetCellIndex(int x, int y);
	int GetCellIndex(int index, int dx, int dy);
	CellType GetCell(int index);
	CellType GetCell(int x, int y);
	void SetCell(int index, CellType cell);
	void SetCell(int x, int y, CellType cell);
	void SetCellRegion(int x, int y, CellType cell, int width, int height);
	int GetWidth();
	int GetHeight();

	void Clear(CellType value, CellType valueBorder);

	void ToOutput();
	void ToOutputField();
	static Map<int>* LoadFrom(std::string &data, std::vector<Point>* specialPoints);

};

#include "Map.inl"

#endif//MOTIONPLAN_MAP_H_
