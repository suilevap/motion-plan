#pragma once
#include "Point.h"
#include "Map.h"

template<class CellType>
class ScaledMap : public Map<CellType>
{
private:
	float _ratio;
	float _cellSize;

public:
	ScaledMap(int width, int height, float cellSize)
	  :Map(width, height, 1)
	{
		_cellSize = cellSize;
		_ratio = 1/cellSize;
		//InitMap(width, height, 1);
	}

	int GetCellIndex(int x, int y)
	{
		return Map<CellType>::GetCellIndex(x * _ratio, y * _ratio);
	}
	
	Point GetCellPoint(int index)
	{
		Point p;
		p = Map<CellType>::GetCellPoint(index);
		p.X *= _cellSize;
		p.Y *= _cellSize;
		return p;
	} 
};
