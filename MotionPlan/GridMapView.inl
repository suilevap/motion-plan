#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#error "Include from GridMapView.h only."
#else

#include "Math.h"

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::GetNeighbors(int& node, std::vector<AStar::EdgeInfo<int,float>>& neighbors)
{
	neighbors.resize(8);
	neighbors[0] = AStar::EdgeInfo<int,float>(node + 1, 1, AStar::NodeStatus::Close);
	neighbors[1] = AStar::EdgeInfo<int,float>(node - 1, 1, AStar::NodeStatus::Close);
	neighbors[2] = AStar::EdgeInfo<int,float>(node + _width, 1, AStar::NodeStatus::Close);
	neighbors[3] = AStar::EdgeInfo<int,float>(node - _width, 1, AStar::NodeStatus::Close);

	neighbors[4] = AStar::EdgeInfo<int,float>(node + 1 + _width, SQRT_2, AStar::NodeStatus::Open);
	neighbors[5] = AStar::EdgeInfo<int,float>(node - 1 + _width, SQRT_2, AStar::NodeStatus::Open);
	neighbors[6] = AStar::EdgeInfo<int,float>(node + 1 - _width, SQRT_2, AStar::NodeStatus::Open);
	neighbors[7] = AStar::EdgeInfo<int,float>(node - 1 - _width, SQRT_2, AStar::NodeStatus::Open);
	
}

template<class CellType, typename CoordType>
Point<CoordType> GridMapView<CellType, CoordType>::GetPoint(int& node)
{
	Point<CoordType> p;
	p.X = node % _width - _border;
	p.Y = node / _width - _border;
	return p;
}
template<class CellType, typename CoordType>
float GridMapView<CellType, CoordType>::GetCostPoint(const Point<CoordType>& p1,const Point<CoordType>& p2)
{
	float cost = AStar::DistanceEvaluator::DiagonalDistance(p1, p2);
	return cost;
}

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::GetNode(Point<CoordType>& point)
{
	return (point.X + _border) + (point.Y + _border) * _width ;
}

template<class CellType, typename CoordType>
CellType GridMapView<CellType, CoordType>::GetCell(int& node)
{
	return _map[node] ;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::SetCell(int& node, CellType cell)
{
	_map[node] = cell;	
}

template<class CellType, typename CoordType>
Point<CoordType> GridMapView<CellType, CoordType>::GetMaxPoint()
{
	Point<CoordType> p;
	p.X = _width - _border * 2;;
	p.Y = _height - _border * 2;;
	return p;
}

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::GetMaxNode()
{
	return _width * _height;
}

template<class CellType, typename CoordType>
inline int GridMapView<CellType, CoordType>::GetBorder()
{
	return _border;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::InitMap(int width, int height, int border)
{
	_border = border;
	_width = width + _border * 2;
	_height = height + _border * 2;
	int size = _width*_height;
	_map = new CellType[size];
	Clear(0,1);
	//_neighbors.i
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView(int width, int height)
{
	InitMap(width, height, 1);
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView(int width, int height, int border)
{
	InitMap(width, height, border);
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::~GridMapView(void)
{
	delete[] _map;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size)
{
	for (int i = point.X; i < (point.X + size.X); i++)
	{
		for (int k = point.Y; k < (point.Y + size.Y); k++)
		{
			_map[GetNode(Point<CoordType>(i,k))] = cell;
		}
	}
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::Clear(CellType value, CellType valueBorder)
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
template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::ToOutput()
{
	Point<CoordType> size = GetMaxPoint();

	int w = size.X;
	int h = size.Y;
	for (int k = 0; k < h; k++)
	{
		for (int i =0; i < w; i++)
		{
			//printf("%3d",(int)( (int)(GetCell(i , k)*10 )%100 ));
			printf("%3d",(int)GetCellPoint(Point<CoordType>(i , k)));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::ToOutputField()
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

template<class CellType, typename CoordType>
GridMapView<int>* GridMapView<CellType, CoordType>::LoadFrom(std::string &data, std::vector<Point<CoordType>>* specialPoints)
{
	int width = data.find("\r\n");
	int height = (data.length()+2) / (width + 2);
	GridMapView<int>* map = new GridMapView<int>(width, height);
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
				Point<CoordType> point(i, k);
				
				(*specialPoints)[idx]=point;
			}
			map->SetCellPoint(Point<CoordType>(i,k), cell);
			index++;
		}
		index+=2;
	}

	return map;
}

#endif
