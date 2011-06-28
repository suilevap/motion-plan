#ifndef MOTIONPLAN_SCALEDMAP_H_
#error "Include from ScaledMap.h only."
#else

template<class CellType>
ScaledMap<CellType>::ScaledMap(int width, int height, float cellSize)
  :Map(width, height, 1)
{
	_cellSize = cellSize;
	_ratio = 1/cellSize;
	//InitMap(width, height, 1);
}

template<class CellType>
int ScaledMap<CellType>::GetCellIndex(int x, int y)
{
	return Map<CellType>::GetCellIndex(x * _ratio, y * _ratio);
}

template<class CellType>
Point ScaledMap<CellType>::GetCellPoint(int index)
{
	Point p;
	p = Map<CellType>::GetCellPoint(index);
	p.X *= _cellSize;
	p.Y *= _cellSize;
	return p;
}

#endif
