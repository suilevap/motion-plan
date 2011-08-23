#ifndef MOTIONPLAN_SPARSEGRIDMAPVIEW_H_
#error "Include from SparseGridMapView.h only."
#else

template<class CellType>
inline int SparseGridMapView<CellType>::GetSparseId(int node)
{
	Point<int> p = GetMapPoint(node);
	p.X /= 2;
	p.Y /= 2;
	int result = (p.X + _border/2) + (p.Y + _border/2) * _width/2 ;
	return result;
}

template<class CellType>
inline int SparseGridMapView<CellType>::GetSparseMainNode(int node)
{
	Point<int> p = GetMapPoint(node);
	p.X &= ~0x01;
	p.Y &= ~0x01;
	int result =GetNodeFromMapPoint(p);
	return result;
}

template<class CellType>
inline bool SparseGridMapView<CellType>::IsCellSparse(int node)
{
	return (_mapSparse[GetSparseId(node)] == 0);
}
template<class CellType>
inline void SparseGridMapView<CellType>::AddCellSparse(int node)
{
	_mapSparse[GetSparseId(node)]++;
}
template<class CellType>
inline void SparseGridMapView<CellType>::RemoveCellSparse(int node)
{
	_mapSparse[GetSparseId(node)]--;
}

template<class CellType>
Point<float> SparseGridMapView<CellType>::GetPoint(int& node)
{

	Point<float> p;
	if (!IsCellSparse(node))
	{
		p = GridMapView<CellType,float>::GetPoint(node);
	}
	else
	{
		int nodeMain = GetSparseMainNode(node);
		p = GridMapView<CellType,float>::GetPoint(nodeMain);
		p.X += _cellSize.X/2;
		p.Y += _cellSize.Y/2;
	}
	return p;
}

template<class CellType>
int SparseGridMapView<CellType>::GetNode(Point<float>& point)
{
	int node = GridMapView<CellType,float>::GetNode(point);
	if (IsCellSparse(node))
	{
		node = GetSparseMainNode(node);
	}
	return node;
}

template<class CellType>
int SparseGridMapView<CellType>::GetNodeWrite(Point<float>& point)
{
	int node = GridMapView<CellType,float>::GetNode(point);
	return node;
}

template<class CellType>
inline void SparseGridMapView<CellType>::GetNeighborsPartialFromSparsed(
	int nodeNeighboor1, 
	int nodeNeighboor2, 
	FastVector<AStar::EdgeInfo<int,float>>& neighbors, 
	float d, 
	float sparceCellD)
{
	if (IsCellSparse(nodeNeighboor1))
	{
		nodeNeighboor1 = GetSparseMainNode(nodeNeighboor1);
		neighbors.push_back(AStar::EdgeInfo<int,float>(nodeNeighboor1, sparceCellD, AStar::NodeStatus::Open));
	}
	else
	{
		neighbors.push_back(AStar::EdgeInfo<int,float>(nodeNeighboor1, d, AStar::NodeStatus::Open));
		neighbors.push_back(AStar::EdgeInfo<int,float>(nodeNeighboor2, d, AStar::NodeStatus::Open));
	}
}

template<class CellType>
inline void SparseGridMapView<CellType>::GetNeighborsPartialFromNotSparsed(
	int nodeNeighboor,  
	FastVector<AStar::EdgeInfo<int,float>>& neighbors, 
	float d, 
	float sparceCellD)
{
	if (IsCellSparse(nodeNeighboor))
	{
		nodeNeighboor = GetSparseMainNode(nodeNeighboor);
		neighbors.push_back(AStar::EdgeInfo<int,float>(nodeNeighboor, sparceCellD, AStar::NodeStatus::Open));
	}
	else
	{
		neighbors.push_back(AStar::EdgeInfo<int,float>(nodeNeighboor, d, AStar::NodeStatus::Open));
	}
}


template<class CellType>
void SparseGridMapView<CellType>::GetNeighbors(int& node, FastVector<AStar::EdgeInfo<int,float>>& neighbors)
{
	neighbors.clear();
    neighbors.resize(16);

	static float step1 = 1;//_cellSize.X;
	static float stepD = SQRT_2;//_cellSize.X * SQRT_2;

	static float stepToSplased = SQRT_2 * SQRT_5 / 2;
	static float stepToSplasedD = stepD * 3 / 2;


	if (!IsCellSparse(node))
	{
		GetNeighborsPartialFromNotSparsed(
			node + 1, 
			neighbors, 
			step1, 
			stepToSplased);
		GetNeighborsPartialFromNotSparsed(
			node - 1, 
			neighbors, 
			step1, 
			stepToSplased);
		GetNeighborsPartialFromNotSparsed(
			node + _width, 
			neighbors, 
			step1, 
			stepToSplased);
		GetNeighborsPartialFromNotSparsed(
			node - _width, 
			neighbors, 
			step1, 
			stepToSplased);
	}
	else
	{
		GetNeighborsPartialFromSparsed(
			node + 2,
			node + 2 + _width, 
			neighbors, 
			stepToSplased, 
			step1 * 2);

		GetNeighborsPartialFromSparsed(
			node - 1,
			node - 1 + _width, 
			neighbors, 
			stepToSplased, 
			step1 * 2);

		GetNeighborsPartialFromSparsed(
			node + _width * 2,
			node + _width * 2 + 1, 
			neighbors, 
			stepToSplased, 
			step1 * 2);

		GetNeighborsPartialFromSparsed(
			node - _width * 2,
			node - _width * 2 + 1, 
			neighbors, 
			stepToSplased, 
			step1 * 2);
	
	}	
}


template<class CellType>
SparseGridMapView<CellType>::SparseGridMapView(float width, float height, float cellWidth)
{
	InitMap(width, height, 4, Point<float>(cellWidth, cellWidth));
	int sparceSize = (_width * _height) / 4;
	_mapSparse = new int[sparceSize];
	memset(_mapSparse, 0, sparceSize * sizeof(_mapSparse[0]));
}

template<class CellType>
SparseGridMapView<CellType>::~SparseGridMapView()
{
	delete[] _mapSparse;
}

template<class CellType>
void SparseGridMapView<CellType>::SetCell(int& node, CellType cell)
{
	int oldCell = GridMapView<CellType>::GetCell(node);

	if (oldCell != cell)
	{
		GridMapView<CellType>::SetCell(node, cell);
		if (cell == 1)
		{
			AddCellSparse(node);
		}
		else
		{
			RemoveCellSparse(node);
		}
	}
}


#endif
