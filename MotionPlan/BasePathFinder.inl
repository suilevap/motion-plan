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
    _map = map;        
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
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo>::
Find(PointInfo start, PointInfo goal)
{
	_goalPoint = goal;
	_start = _map->GetNode(start);
	_goal = _map->GetNode(goal);
	//TODO: fix several return!!
	if ((_map->GetCell(_start) == 1) ||(_map->GetCell(_goal) == 1))
	{
		return Path<Point>::Empty();
	}

	//TODO: donot use vector explicitly
	_mapCost.clear();

	_mapCost.resize(_map->GetMaxNode(),NodeState<NodeInfo,CostInfo>());

	_queue = new CellQueue<NodeInfo,CostInfo>();

	 //_mapParent[_start] = _start;

	PathNode<int,float> pathNode(_start, 0, 0);

	_mapCost[_start] = NodeState<NodeInfo, CostInfo>(_start, 0);


	_queue->Push(pathNode);

	bool pathFound = false;
	while (!_queue->Empty() && !pathFound)
	{

		pathNode = _queue->Pop();
		NodeInfo node = pathNode.Node;
		if (node != _goal)
		{
			Step(node);
		}
		else
		{
			pathFound = true;
		}
	}

	delete _queue;

	Path<Point>* result;
	if (pathFound)
	{
		result = ExtractPath();
	}
	else
	{
		result = Path<Point>::Empty();
	}
	return result;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
	void BasePathFinder<PointInfo, CellType, CostInfo>::Step(int node)
{
	_mapCost[node].Status = NodeStatus::Close;
	_map->GetNeighbors(node, _neighbors);
	for(std::vector<AStar::EdgeInfo<NodeInfo,CostInfo>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it)
	{
		if (_mapCost[it->To].Status == NodeStatus::Open)
		{
			CheckNeighbor(node, *it);
			/*if (it->Cost == 1)
			{
				_mapCost[it->To].Status = NodeStatus::Close;
			}*/
		}
	}
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
bool BasePathFinder<PointInfo, CellType, CostInfo>::
CheckNeighbor(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge)
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

			CostInfo estimate = GetEstimateDistance(newNode);
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
CostInfo BasePathFinder<PointInfo, CellType, CostInfo>::GetEstimateDistance(NodeInfo& node)
{
	Point p = _map->GetPoint(node);
	return _map->GetCostPoint(p, _goalPoint);
	//return _map->GetCost(node, _goal);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo>::ExtractPath()
{
	PointInfo point;
	
	std::vector<PointInfo> result;
	NodeInfo pos = _goal;
	
	result.push_back(_map->GetPoint(_goal));
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

#endif