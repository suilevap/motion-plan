#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#error "Include from GridMapView.h only."
#else

#include "Math.h"

template<class CellType>
void GridMapView<CellType>::GetNeighbors(NodeInfo& node, std::vector<Edge>& neighbors)
{
	neighnodebors.reserve(8);

	neighbors[0].To = node+1;
	neighbors[0].Cost = 1;
	neighbors[1].To = node-1;
	neighbors[1].Cost = 1;
	neighbors[2].To = node+_width;
	neighbors[2].Cost = 1;
	neighbors[3].To = node-_width;
	neighbors[3].Cost = 1;

	neighbors[4].To = node+1 + width;
	neighbors[4].Cost = SQRT_2;
	neighbors[5].To = node-1 + _width;
	neighbors[5].Cost = SQRT_2;
	neighbors[6].To = node +1 - _width;
	neighbors[6].Cost = SQRT_2;
	neighbors[7].To = node -1 -_width;
	neighbors[7].Cost = SQRT_2;
	
}

template<class CellType>
PointInfo GridMapView<CellType>::GetPoint(NodeInfo& node)
{
	PointInfo p;
	p.X = index % _width - _border;
	p.Y = index / _width - _border;
	return p;
}
template<class CellType>
GridMapView::CostInfo GridMapView<CellType>::GetCost(GridMapView::NodeInfo& node1, GridMapView::NodeInfo& node2)
{
	PointInfo p1 = GetPoint(node1);
	PointInfo p2 = GetPoint(node2);
	CostInfo cost = DistanceEvaluator::DiagonalDistance<CostInfo>(p1.X, p1.Y, p2.X, p2.Y);
	return cost;
}

template<class CellType>
GridMapView::NodeInfo GridMapView<CellType>::GetNode(GridMapView::PointInfo& point)
{
	return (x + _border) + (y + _border) * _width ;
}

template<class CellType>
CellType GridMapView<CellType>::GetCell(GridMapView::NodeInfo& node)
{
	return _map[index] ;
}

template<class CellType>
void GridMapView<CellType>::SetCell(GridMapView::NodeInfo& index, CellType cell)
{
	_map[index] = cell;
}

template<class CellType>
GridMapView::PointInfo GridMapView<CellType>::GetMaxPoint()
{
	PointInfo p;
	p.X = _width - _border * 2;;
	p.Y = _height - _border * 2;;
	return p;
}

template<class CellType>
GridMapView::NodeInfo GridMapView<CellType>::GetMaxNode()
{
	return _width * _height;
}

template<class CellType>
inline int GridMapView<CellType>::GetBorder()
{
	return _border;
}

template<class CellType>
void GridMapView<CellType>::InitMap(int width, int height, int border)
{
	_border = border;
	_width = width + _border * 2;
	_height = height + _border * 2;
	int size = _width*_height;
	_map = new CellType[size];
	Clear(0,1);
	//_neighbors.i
}

template<class CellType>
GridMapView<CellType>::GridMapView(int width, int height)
{
	InitMap(width, height, 1);
}

template<class CellType>
GridMapView<CellType>::GridMapView(int width, int height, int border)
{
	InitMap(width, height, border);
}

template<class CellType>
GridMapView<CellType>::~GridMapView(void)
{
	delete[] _map;
}

template<class CellType>
void GridMapView<CellType>::SetCellRegion(GridMapView::PointInfo& point, CellType cell, GridMapView::PointInfo& size)
{
	for (int i = point.X; i < (point.X + size.X); i++)
	{
		for (int k = point.Y; k < (point.Y + size.Y); k++)
		{
			_map[GetCellIndex(i,k)] = cell;
		}
	}
}

template<class CellType>
void GridMapView<CellType>::Clear(CellType value, CellType valueBorder)
{
	int size = _width*_height;
	int sizeCell = sizeof(_map[0]);
	memset(_map, value, sizeCell*size);
	if (value != valueBorder)
	{
		for (int i = 0; i < _height; ++i)
		{
			for (int k = 0; k < _border; ++k)
			{
				_map[i * _width + k] = valueBorder;
				_map[i * _width + _width - k - 1] = valueBorder;
			}
		}
		for (int k = _border; k < _width - _border; ++k)
		{
			for (int i = 0; i < _border; ++i)
			{
				_map[i * _width + k] = valueBorder;
				_map[(_height - i - 1) * _width + k] = valueBorder;
			}
		}

	}
}

//only for test!!
template<class CellType>
void GridMapView<CellType>::ToOutput()
{
	int w = GetWidth();
	int h = GetHeight();
	for (int k = 0; k < h; k++)
	{
		for (int i =0; i < w; i++)
		{
			//printf("%3d",(int)( (int)(GetCell(i , k)*10 )%100 ));
			printf("%3d",(int)GetCell(i , k));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType>
void GridMapView<CellType>::ToOutputField()
{
	const char * presentation = "\\|/-.-/|\\";
	int w = GetWidth();
	int h = GetHeight();
	for (int k = 0; k < h; k++)
	{
		for (int i =0; i < w; i++)
		{
			int dx;
			int dy;
			int ind1 = (int)GetCell(i , k);
			int ind2 = GetCellIndex(i, k);
			GetD(ind1, ind2, &dx, &dy);
			char s;
			if (ind1 != 0)
			{
				s = presentation[(dx+1)+(dy+1)*3];
			}
			else
			{
				s = '.';
			}
			printf("%c", s);
			//printf("%3d",(dx+1)*10+(dy+1));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType>
GridMapView<int>* GridMapView<CellType>::LoadFrom(std::string &data, std::vector<Point>* specialPoints)
{
	int width = data.find("\r\n");
	int height = (data.length()+2) / (width + 2);
	Map<int>* map = new Map<int>(width, height);
	specialPoints->resize(10);
	int index = 0;
	int cell;
	for (int k = 0; k < height; k++)
	{
		for (int i = 0; i < width; i++)
		{
			char symbol=data[index];
			if (symbol =='#')
			{
				cell = 1;
			}
			else
			{
				cell = 0;
			}
			if ((symbol>='0') && (symbol<='9'))
			{
				int idx = (int)(symbol-'0');
				Point point;
				point.X = i;
				point.Y = k;
				(*specialPoints)[idx]=point;
			}
			map->SetCell(PointInfo(i,k), cell);
			index++;
		}
		index+=2;
	}

	return map;
}

#endif
