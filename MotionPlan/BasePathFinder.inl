#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#error "Include from BasePathFinder.h only."
#else

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
BasePathFinder<PointInfo, CellType, CostInfo>::
BasePathFinder(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map)
{
	Init(map);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
BasePathFinder<PointInfo, CellType, CostInfo>::
~BasePathFinder()
{
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BasePathFinder<PointInfo, CellType, CostInfo>::
Init(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map)
{
    _map = map;
	_queue = new CellQueue<NodeInfo,CostInfo>();
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BasePathFinder<PointInfo, CellType, CostInfo>::
FindStart(NodeInfo start, NodeInfo goal)
{
	_start = start;
	_goal = goal;
	//TODO: donot use vector explicitly
	_mapCost.clear();

	_mapCost.resize(_map->GetMaxNode(),NodeState<NodeInfo,CostInfo>());
	
	_queue->Clear();	

	 //_mapParent[_start] = _start;

	PathNode<int,float> pathNode(_start, 0, 0);

	_mapCost[start] = NodeState<NodeInfo, CostInfo>(_start, 0);

	_queue->Push(pathNode);
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
int BasePathFinder<PointInfo, CellType, CostInfo>::
FindStep()
{
#ifdef _DEBUG
	static int i = 0;
	if (i++%1023 == 0)
	{
		//ToOutputCurrentState();
	}
#endif
	PathNode<int,float> pathNode = _queue->Pop();
	NodeInfo node = pathNode.Node;
	Step(node, _goal);		
	return node;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
bool BasePathFinder<PointInfo, CellType, CostInfo>::
IsGoal(NodeInfo& node)
{
	return (node == _goal);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
bool BasePathFinder<PointInfo, CellType, CostInfo>::
FindIsPathExists(NodeInfo& node)
{
	return (_mapCost[node].Status == NodeStatus::Close);
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo>::
FindEnd(NodeInfo& node)
{
	Path<PointInfo>* result;
	if (FindIsPathExists(node))
	{
		result = ExtractPath(node);
	}
	else
	{
		result = Path<PointInfo>::Empty();
	}
#ifdef _DEBUG
	ToOutputCurrentState();
#endif
	return result;
}

//template<
//	typename PointInfo, 
//	typename CellType, 	
//	typename CostInfo> 
//Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo>::
//Find(PointInfo start, PointInfo goal)
//{
//	_goalPoint = goal;
//	_start = _map->GetNode(start);
//	_goal = _map->GetNode(goal);
//	//TODO: fix several return!!
//	if ((_map->GetCell(_start) == 1) ||(_map->GetCell(_goal) == 1))
//	{
//		return Path<PointInfo>::Empty();
//	}
//
//	//TODO: donot use vector explicitly
//	_mapCost.clear();
//
//	_mapCost.resize(_map->GetMaxNode(),NodeState<NodeInfo,CostInfo>());
//
//	_queue = new CellQueue<NodeInfo,CostInfo>();
//
//	 //_mapParent[_start] = _start;
//
//	PathNode<int,float> pathNode(_start, 0, 0);
//
//	_mapCost[_start] = NodeState<NodeInfo, CostInfo>(_start, 0);
//
//
//	_queue->Push(pathNode);
//
//	bool pathFound = false;
//	while (!_queue->Empty() && !pathFound)
//	{
//#ifdef _DEBUG
//		//ToOutputCurrentState();
//#endif
//		pathNode = _queue->Pop();
//		NodeInfo node = pathNode.Node;
//		if (node != _goal)
//		{
//			Step(node, _goal);
//		}
//		else
//		{
//			pathFound = true;
//#ifdef _DEBUG
//			ToOutputCurrentState();
//#endif
//		}
//	}
//
//	delete _queue;
//
//	Path<PointInfo>* result;
//	if (pathFound)
//	{
//		result = ExtractPath();
//	}
//	else
//	{
//		result = Path<PointInfo>::Empty();
//	}
//	return result;
//}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BasePathFinder<PointInfo, CellType, CostInfo>::
Step(NodeInfo& node, NodeInfo& goal)
{
	_mapCost[node].Status = NodeStatus::Close;
	_map->GetNeighbors(node, _neighbors);
	for(std::vector<AStar::EdgeInfo<NodeInfo,CostInfo>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it)
	{
		if (_mapCost[it->To].Status == NodeStatus::Open)
		{
			CheckNeighbor(node, *it, goal);
			//_mapCost[it->To].Status = it->InitStatus;//NodeStatus::Open;
		}
	}
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
bool BasePathFinder<PointInfo, CellType, CostInfo>::
CheckNeighbor(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge, NodeInfo& goal)
{
	bool result = false;
	NodeInfo newNode = edge.To;
	//TODO: fix magic if cell==0
	if (_map->GetCell(newNode) == 0)
	{
		//TODO: fix hardcoded _mapDist for NodeInfo == int
		NodeState<NodeInfo,CostInfo>& bestResult = _mapCost[newNode];

		CostInfo cost = GetDistance(node, edge);
		if ((bestResult.ParentNode == 0) 
			|| (bestResult.Cost > cost))
		{
			//TODO: fix hardcoded _mapDist for NodeInfo == int

			CostInfo estimate = GetEstimateDistance(newNode, goal);//*96.0f/128;
			PathNode<NodeInfo, CostInfo> pathNode(newNode, cost, estimate );
			_queue->Push(pathNode);
			_mapCost[newNode] = NodeState<NodeInfo, CostInfo>(node, cost);
			result = true;
		}
	}
	return result;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
CostInfo BasePathFinder<PointInfo, CellType, CostInfo>::
GetDistance(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge)
{
	return _mapCost[node].Cost + edge.Cost;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
inline CostInfo BasePathFinder<PointInfo, CellType, CostInfo>::
GetEstimateDistance(NodeInfo& node1, NodeInfo& node2)
{
	return _map->GetCost(node1, node2);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo>::
ExtractPath(NodeInfo& toPoint)
{
	PointInfo point;
	
	std::vector<PointInfo> result;
	NodeInfo pos = toPoint;
	
	result.push_back(_map->GetPoint(pos));
	while (pos != _start)
	{		
		pos = _mapCost[pos].ParentNode;
		point = _map->GetPoint(pos);
		result.push_back(point);
	}
	
	reverse(result.begin(), result.end());
	Path<PointInfo>* path = new Path<PointInfo>(result);
	return path;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BasePathFinder<PointInfo, CellType, CostInfo>::
ToOutputCurrentState()
{

	if (_mapForStateDebug != NULL)
	{
		for (int i =0; i < _mapCost.size(); ++i)
		{
			_mapForStateDebug->SetCell(i, ((int)_mapCost[i].Cost%10));
			//_mapForStateDebug->SetCell(i, ((int) GetEstimateDistance(i, _goal)%10)+1);
		}
		_mapForStateDebug->ToOutput();
	}
}


#endif
