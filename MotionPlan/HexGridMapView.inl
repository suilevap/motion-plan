#ifndef MOTIONPLAN_HEXGRIDMAPVIEW_H_
#error "Include from HexGridMapView.h only."
#else

template<class CellType>
inline int HexGridMapView<CellType>::GetYOffset(int node)
{
	//check that column is even
	return (node % _width - _border) & 0x01;
}

template<class CellType>
inline int HexGridMapView<CellType>::GetYOffset(const Point<float>& point)
{
	//check that column is even
	return static_cast<int>(point.X * _scale.X ) & 0x01;
}

template<class CellType>
std::vector<AStar::EdgeInfo<int,float>>::iterator HexGridMapView<CellType>::GetNeighbors(int& node, std::vector<AStar::EdgeInfo<int,float>>& neighbors)
{
	neighbors.resize(6);
	int offset = GetYOffset(node);
	int secondNeighborOffset = _width * (-1 + offset*2);

	neighbors[0] = AStar::EdgeInfo<int,float>(node + 1, 1, AStar::NodeStatus::Close);
	neighbors[1] = AStar::EdgeInfo<int,float>(node + 1 + secondNeighborOffset, 1, AStar::NodeStatus::Close);

	neighbors[2] = AStar::EdgeInfo<int,float>(node - 1, 1, AStar::NodeStatus::Close);
	neighbors[3] = AStar::EdgeInfo<int,float>(node - 1 + secondNeighborOffset, 1, AStar::NodeStatus::Close);

	neighbors[4] = AStar::EdgeInfo<int,float>(node + _width, 1, AStar::NodeStatus::Close);
	neighbors[5] = AStar::EdgeInfo<int,float>(node - _width, 1, AStar::NodeStatus::Close);
	return neighbors.end();
}

template<class CellType>
Point<float> HexGridMapView<CellType>::GetPoint(int& node)
{
	Point<float> p = GridMapView<CellType,float>::GetPoint(node);
	int offset = GetYOffset(node);
	p.Y += _cellSize.Y/2 * offset;
	return p;
}

template<class CellType>
int HexGridMapView<CellType>::GetNode(Point<float>& point)
{
	int offset = GetYOffset(point);
	Point<float> p = point;
	p.Y -= _cellSize.Y/2 * offset;
	int node = GridMapView<CellType,float>::GetNode(p);
	return node;
}

template<class CellType>
float HexGridMapView<CellType>::GetCost(const int& nodeStart,const int& nodeGoal)
{
	Point<int> p1 = GetMapPoint(nodeStart);
	Point<int> p2 = GetMapPoint(nodeGoal);
	float cost = AStar::DistanceEvaluator::HexShiftByXDistance<float>(p1, p2);
	return cost;
}

template<class CellType>
HexGridMapView<CellType>::HexGridMapView(float width, float height, float cellWidth)
{
	InitMap(width, height, 1, Point<float>(cellWidth * SQRT_075, cellWidth));
}

template<class CellType>
void HexGridMapView<CellType>::ToOutput()
{
	Point<float> size = GetMaxPoint();
	Point<int> mapCellSize;
	TransformPointToCell(size, mapCellSize);
	int w = mapCellSize.X;
	int h = mapCellSize.Y;
	for (int i = 0; i < w; i ++)
	{
		
		int offset = GetYOffset(GetNodeFromMapPoint(Point<int>(i, 0)));
		if (offset == 1)
		{
			printf(" ");
		}
		for (int k = 0; k < h; k ++)
		{			
			int node = GetNodeFromMapPoint(Point<int>(i, k));
			printf("%2d",(int)GetCell(node));
		}
		printf("\n");
	}
	printf("========================\n");
}


#endif
