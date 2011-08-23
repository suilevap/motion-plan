#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#error "Include from BasePathFinder.h only."
#else

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
BasePathFinder(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map)
{
	Init(map);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
~BasePathFinder()
{
	delete _queue;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
void BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
Init(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map)
{
    _map = map;
	_queue = new CellQueue();
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
void BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
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
	typename CostInfo,
	typename CellQueue>
int BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
FindStep()
{
#ifdef _DEBUG
	static int i = 0;
	if (i++%1023 == 0)
	{
		//ToOutputCurrentState();
	}
#endif
	NodeInfo node = NULL;
	if (!_queue->Empty())
	{
		PathNode<int,float> pathNode = _queue->Pop();
		node = pathNode.Node;
		Step(node, _goal);
	}
	return node;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
bool BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
IsGoal(NodeInfo& node)
{
	return (node == _goal);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
bool BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
FindIsPathExists(NodeInfo& node)
{
	return ((node!=NULL) && (_mapCost[node].Status == NodeStatus::Close));
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
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


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
void BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
Step(NodeInfo& node, NodeInfo& goal)
{
	_mapCost[node].Status = NodeStatus::Close;
	_map->GetNeighbors(node, _neighbors);
	//for(std::vector<AStar::EdgeInfo<NodeInfo,CostInfo>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it)
    int size = _neighbors.size();
    for (int i=0; i < size; ++i)
	{
        EdgeInfo<NodeInfo,CostInfo>& edge = _neighbors[i];
		if (_mapCost[edge.To].Status == NodeStatus::Open)
		{
			CheckNeighbor(node, edge, goal);
			//_mapCost[it->To].Status = it->InitStatus;//NodeStatus::Open;
		}
	}
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
bool BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
CheckNeighbor(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge, NodeInfo& goal)
{
	bool result = false;
	NodeInfo newNode = edge.To;

	//TODO: fix hardcoded _mapDist for NodeInfo == int
	NodeState<NodeInfo,CostInfo>& bestResult = _mapCost[newNode];

	CostInfo cost = GetDistance(node, edge);
	if ((bestResult.ParentNode == 0) 
		|| (bestResult.Cost > cost))
	{
		//TODO: fix hardcoded _mapDist for NodeInfo == int
		CostInfo estimate;
		if (CellQueue::UseHeuristic)
		{
			estimate = GetEstimateDistance(newNode, goal);//*96.0f/128;
		}
        else
        {
            estimate = 0;
        }
		
		PathNode<NodeInfo, CostInfo> pathNode(newNode, cost, estimate );
		_queue->Push(pathNode);

        bestResult.ParentNode = node;
        bestResult.Cost = cost;
		result = true;
	}

	return result;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
CostInfo BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
GetDistance(NodeInfo& node, EdgeInfo<NodeInfo, CostInfo>& edge)
{
	return _mapCost[node].Cost + edge.Cost;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
inline CostInfo BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
GetEstimateDistance(NodeInfo& node1, NodeInfo& node2)
{
	return _map->GetCost(node1, node2);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
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
	typename CostInfo,
	typename CellQueue>
void BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
ToOutputCurrentState()
{
#ifdef DEBUG_OUTPUT
	if (_mapForStateDebug != NULL)
	{
		for (int i =0; i < _mapCost.size(); ++i)
		{
			_mapForStateDebug->SetCell(i, ((int)_mapCost[i].Cost%10));
			//_mapForStateDebug->SetCell(i, ((int) GetEstimateDistance(i, _goal)%10)+1);
		}
		_mapForStateDebug->ToOutput();
	}
#endif
}


#endif
