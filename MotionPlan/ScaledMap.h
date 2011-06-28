#pragma once

#ifndef MOTIONPLAN_SCALEDMAP_H_
#define MOTIONPLAN_SCALEDMAP_H_

#include "Point.h"
#include "Map.h"

template<class CellType>
class ScaledMap : public Map<CellType>
{
private:
	float _ratio;
	float _cellSize;

public:
	ScaledMap(int width, int height, float cellSize);

	int GetCellIndex(int x, int y);
	
	Point GetCellPoint(int index);
};

#include "ScaledMap.inl"

#endif//MOTIONPLAN_SCALEDMAP_H_