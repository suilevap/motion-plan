#ifndef MOTIONPLAN_GRIDMAPVIEW_H_
#error "Include from GridMapView.h only."
#else

#include "DistanceEvaluator.h"
#include "MathConstants.h"

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::GetNeighbors(int& node, std::vector<AStar::EdgeInfo<int,float>>& neighbors)
{
	neighbors.resize(8);
	//neighbors.clear();

	static float step1 = 1;//_cellSize.X;
	static float stepD = SQRT_2;//_cellSize.X * SQRT_2;
    int i = 0;
    i = AddNeighbor(node + 1, step1, neighbors, i);
    i = AddNeighbor(node - 1, step1, neighbors, i);
    i = AddNeighbor(node + _width, step1, neighbors, i);
    i = AddNeighbor(node - _width, step1, neighbors, i);

    i = AddNeighbor(node + 1 + _width, stepD, neighbors, i);
    i = AddNeighbor(node - 1 + _width, stepD, neighbors, i);
    i = AddNeighbor(node + 1 - _width, stepD, neighbors, i);
    i = AddNeighbor(node - 1 - _width, stepD, neighbors, i);

    return i;
	//neighbors[0] = AStar::EdgeInfo<int,float>(node + 1, step1, AStar::NodeStatus::Close);
	//neighbors[1] = AStar::EdgeInfo<int,float>(node - 1, step1, AStar::NodeStatus::Close);
	//neighbors[2] = AStar::EdgeInfo<int,float>(node + _width, step1, AStar::NodeStatus::Close);
	//neighbors[3] = AStar::EdgeInfo<int,float>(node - _width, step1, AStar::NodeStatus::Close);

	//neighbors[4] = AStar::EdgeInfo<int,float>(node + 1 + _width, stepD, AStar::NodeStatus::Open);
	//neighbors[5] = AStar::EdgeInfo<int,float>(node - 1 + _width, stepD, AStar::NodeStatus::Open);
	//neighbors[6] = AStar::EdgeInfo<int,float>(node + 1 - _width, stepD, AStar::NodeStatus::Open);
	//neighbors[7] = AStar::EdgeInfo<int,float>(node - 1 - _width, stepD, AStar::NodeStatus::Open);	
}
template<class CellType, typename CoordType>
inline int GridMapView<CellType, CoordType>::
AddNeighbor(int node, float d, std::vector<AStar::EdgeInfo<int,float>>& neighbors, int i)
{
    if (GetCell(node) != 1)
    {
        neighbors[i] =(AStar::EdgeInfo<int,float>(node, d, AStar::NodeStatus::Open));
        //neighbors.push_back(AStar::EdgeInfo<int,float>(node, d, AStar::NodeStatus::Open));
        i++;
    }
    return i;
}

template<class CellType, typename CoordType>
inline void GridMapView<CellType, CoordType>::TransformPointToCell(Point<CoordType>& pointFrom, Point<int>& pointTo)
{
	pointTo.X = static_cast<int>(pointFrom.X * _scale.X );
	pointTo.Y = static_cast<int>(pointFrom.Y * _scale.Y );	
}
template<class CellType, typename CoordType>
inline void GridMapView<CellType, CoordType>::TransformPointToWorld(Point<int>& pointFrom, Point<CoordType>& pointTo)
{
	pointTo.X = static_cast<CoordType>((pointFrom.X + 0.5) * _cellSize.X );
	pointTo.Y = static_cast<CoordType>((pointFrom.Y + 0.5) * _cellSize.Y );
}

template<class CellType, typename CoordType>
inline Point<int> GridMapView<CellType, CoordType>::GetMapPoint(int node)
{
	Point<int> pointMap;
	pointMap.X = node % _width - _border;
	pointMap.Y = node / _width - _border;
	return pointMap;
}
template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>:: GetNodeFromMapPoint(const Point<int>& pointMap)
{
	return (pointMap.X + _border) + (pointMap.Y + _border) * _width ;
}

template<class CellType, typename CoordType>
Point<CoordType> GridMapView<CellType, CoordType>::GetPoint(int& node)
{
	Point<CoordType> pointWorld;
	Point<int> pointMap = GetMapPoint(node);

	TransformPointToWorld(pointMap, pointWorld );
	return pointWorld;
}
template<class CellType, typename CoordType>
float GridMapView<CellType, CoordType>::GetCost(const int& nodeStart,const int& nodeGoal)
{
	Point<int> p1 = GetMapPoint(nodeStart);
	Point<int> p2 = GetMapPoint(nodeGoal);
	float cost = AStar::DistanceEvaluator::DiagonalDistance<float>(p1, p2);
	return cost;
}

template<class CellType, typename CoordType>
int GridMapView<CellType, CoordType>::GetNode(Point<CoordType>& pointWorld)
{
	Point<int >pointMap;
	TransformPointToCell(pointWorld, pointMap);
	return GetNodeFromMapPoint(pointMap);
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
	Point<int> p;
	p.X = _width - _border * 2 - 1;
	p.Y = _height - _border * 2 - 1;
	Point<CoordType> result;
	TransformPointToWorld(p, result);
	result.X += _cellSize.X / 2;
	result.Y += _cellSize.Y / 2;

	return result;
}

template<class CellType, typename CoordType>
bool GridMapView<CellType, CoordType>::OnMap(Point<CoordType>& point)
{
	Point<CoordType> maxPoint = GetMaxPoint();
	return ((point.X >= 0) &&(point.Y >= 0)&&(point.X < maxPoint.X)&&(point.Y < maxPoint.Y));
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
void GridMapView<CellType, CoordType>::InitMap(CoordType width, CoordType height, int border, Point<CoordType> cellSize)
{
	_cellSize = cellSize;
	_scale = Point<float>(1.0f / _cellSize.X, 1.0f / _cellSize.Y);

	Point<int> mapSize;
	TransformPointToCell(Point<CoordType>(width, height), mapSize);

	_border = border;
	_width = mapSize.X + 1 + _border * 2;
	_height = mapSize.Y + 1 + _border * 2;
	int size = _width * _height;
	_map = new CellType[size];
	Clear(0,1);

}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView(CoordType width, CoordType height)
{
	InitMap(width, height, 1, Point<CoordType>(1,1));
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView(CoordType width, CoordType height, CoordType cellWidth)
{
	InitMap(width, height, 1, Point<CoordType>(cellWidth, cellWidth));
}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::GridMapView()
{
	
}

//template<class CellType, typename CoordType>
//GridMapView<CellType, CoordType>::GridMapView(int width, int height, int border)
//{
//	InitMap(width, height, border);
//}

template<class CellType, typename CoordType>
GridMapView<CellType, CoordType>::~GridMapView(void)
{
	delete[] _map;
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::SetCellRegion(Point<CoordType>& point, CellType cell, Point<CoordType>& size)
{

	for (float i = point.X; i < (point.X + size.X); i += _cellSize.X/2)
	{
		for (float k = point.Y; k < (point.Y + size.Y); k += _cellSize.Y/2)
		{
			int node = GetNodeWrite(Point<CoordType>(i,k));
			SetCell(node, cell);
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

	float w = size.X;
	float h = size.Y;
	for (float k = 0; k < h; k += _cellSize.Y)
	{
		for (float i =0; i < w; i += _cellSize.X)
		{
			//printf("%3d",(int)( (int)(GetCell(i , k)*10 )%100 ));
			printf("%2d",(int)GetCellPoint(Point<CoordType>(i , k)));
		}
		printf("\n");
	}
	printf("========================\n");
}

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::ToOutputField()
{
	const char * presentation = "\\|/-.-/|\\";
	Point<CoordType> size = GetMaxPoint();

	int w = size.X;
	int h = size.Y;
	for (int k = 0; k < h; k += _cellSize.Y)
	{
		for (int i =0; i < w; i += _cellSize.X)
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

template<class CellType, typename CoordType>
void GridMapView<CellType, CoordType>::LoadFromVector(std::vector<float>& data)
{
	for (int i = 0; i < data.size(); ++i)
	{
		SetCell(i, data[i]);
	}
}

#endif
