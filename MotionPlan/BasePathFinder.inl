#ifndef MOTIONPLAN_ASTAR_BASEPATHFINDER_H
#error "Include from BasePathFinder.h only."
#else

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
BasePathFinder(MapView<PointInfo, CellType, CostInfo>* map)
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
Init(MapView<PointInfo, CellType, CostInfo>* map)
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
FindStart(PointInfo start, PointInfo goal)
{
    _start = _map->GetNode(start);
    _goal = _map->GetNode(goal);
    _mapCost.clear();

    _mapCost.resize(_map->GetMaxNode(),NodeState<NodeInfo,CostInfo>());

    _queue->Clear();	
    _pathNodePool.Clear();
     //_mapParent[_start] = _start;
    _goalState.Node = 0;
    _goalState.Rank = 0;

    _map->GetPointNeighbors(start, _neighbors);
    //parent for first frontier is 0
    int parentNode = 0;
    ProcessNeighboors(parentNode);
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
		PathNode<NodeInfo, CostInfo>* pathNode = _queue->Pop();
		node = pathNode->Node;
		Step(node);
        _pathNodePool.Free(pathNode);
	}
	return node;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
bool BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
IsGoal(NodeInfo node)
{
	return (node == _goal);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
bool BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
FindIsPathExists(NodeInfo node)
{
	return ((node!=NULL) && (_mapCost[node].Status == NodeStatus::Close));
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
FindEnd(PointInfo point)
{
	Path<PointInfo>* result;
    int node = _map->GetNode(point);
	if (FindIsPathExists(node))
	{
		result = ExtractPath(point);
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
Step(NodeInfo node)
{
	_mapCost[node].Status = NodeStatus::Close;
	_map->GetNeighbors(node, _neighbors);
    ProcessNeighboors(node);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
inline void BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
ProcessNeighboors(int parentNode)
{
	//for(std::vector<AStar::EdgeInfo<NodeInfo,CostInfo>>::iterator it = _neighbors.begin(); it != _neighbors.end(); ++it)
    int size = _neighbors.size();
    for (int i=0; i < size; ++i)
	{
		//TODO: fix C4238: nonstandard extension used : class rvalue used as lvalue	
        EdgeInfo<NodeInfo,CostInfo>* edge = &(_neighbors[i]);
		if (_mapCost[edge->To].Status == NodeStatus::Open)
		{
			CheckNeighbor(parentNode, *edge);
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
CheckNeighbor(NodeInfo node, EdgeInfo<NodeInfo, CostInfo>& edge)
{
	bool result = false;
	NodeInfo newNode = edge.To;

	//TODO: fix hardcoded _mapDist for NodeInfo == int
	NodeState<NodeInfo,CostInfo>* bestResult = &(_mapCost[newNode]);

	CostInfo cost = GetDistance(node, edge);
	if ((bestResult->ParentNode == 0) 
		|| (bestResult->Cost > cost))
	{
		//TODO: fix hardcoded _mapDist for NodeInfo == int
		CostInfo estimate;
		if (CellQueue::UseHeuristic)
		{
			estimate = GetEstimateDistance(newNode);//*96.0f/128;
		}
        else
        {
            estimate = 0;
        }
		PathNode<NodeInfo, CostInfo>* pathNode = _pathNodePool.Allocate();
        pathNode->Node = newNode;
        pathNode->Rank = cost + estimate;
		//PathNode<NodeInfo, CostInfo> pathNode(newNode, cost, estimate );
		_queue->Push(pathNode);

        bestResult->ParentNode = node;
        bestResult->Cost = cost;
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
GetDistance(NodeInfo node, EdgeInfo<NodeInfo, CostInfo>& edge)
{
	return _mapCost[node].Cost + edge.Cost;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
inline CostInfo BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
GetEstimateDistance(NodeInfo node1)
{
	return _map->GetCostFromNode(node1, _goalP);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
int BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
GetNearestNode(PointInfo toPoint)
{
    int minRankNode;
    _map->GetPointNeighbors(toPoint, _neighbors);
    int size = _neighbors.size();
    if (size > 0)
    {
        EdgeInfo<NodeInfo,CostInfo>* edge = &(_neighbors[0]);
        
        minRankNode = edge->To;
        CostInfo minCost = GetDistance(edge->To, (*edge));
        CostInfo cost;
        for (int i = 1; i < size; ++i)
	    {
		    //TODO: fix C4238: nonstandard extension used : class rvalue used as lvalue	
            edge = &(_neighbors[i]);
            cost = GetDistance(edge->To, (*edge));
		    if (cost < minCost)
		    {
                minCost = cost;
                minRankNode = edge->To;
		    }
	    }
    }
    return minRankNode;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueue>
Path<PointInfo>* BasePathFinder<PointInfo, CellType, CostInfo, CellQueue>::
ExtractPath(PointInfo toPoint)
{
	PointInfo point = toPoint;
	
	std::vector<PointInfo> result;
	NodeInfo pos = GetNearestNode(point);
    result.push_back(point);

	do
	{		
		point = _map->GetPoint(pos);
		result.push_back(point);
		pos = _mapCost[pos].ParentNode;
	}
    while (pos != 0);

    result.push_back(_startP);
	
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
