#ifndef MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H
#error "Include from BidirectionalPathFinder.h only."
#else

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
BidirectionalPathFinder(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map)
{
	Init(map);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
~BidirectionalPathFinder()
{
	delete _pathFinderStart;
	delete _pathFinderGoal;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
Init(MapView<PointInfo, CellType, NodeInfo, CostInfo>* map)
{
    _map = map;
	_pathFinderStart = new AStar::BasePathFinder<PointInfo, CellType, CostInfo>(_map);
	_pathFinderGoal = new AStar::BasePathFinder<PointInfo, CellType, CostInfo>(_map);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
FindStart(NodeInfo start, NodeInfo goal)
{
	_pathFinderStart->FindStart(start, goal);
	_pathFinderGoal->FindStart(goal, start);
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
int BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
FindStep()
{
	int result;
	result = _pathFinderStart->FindStep();
	_pathFinderGoal->FindStep();
	return result;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
bool BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
IsGoal(NodeInfo& node)
{
	bool result = (_pathFinderGoal->FindIsPathExists(node));
	return result;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
bool BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
FindIsPathExists(NodeInfo& node)
{
	bool result = (_pathFinderStart->FindIsPathExists(node));
	return result;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
Path<PointInfo>* BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
FindEnd(NodeInfo& node)
{
	Path<PointInfo>* result;
	if (FindIsPathExists(node))
	{
		Path<PointInfo>* path1 = _pathFinderStart->FindEnd(node);
		Path<PointInfo>* path2 = _pathFinderGoal->FindEnd(node);
		std::vector<PointInfo> path2Vector = path2->GetPoints();
		reverse(path2Vector.begin(), path2Vector.end());
		path1->AddPoints(path2Vector);
		delete path2;
		result = path1;
	}
	else
	{
		result = Path<PointInfo>::Empty();
	}

	return result;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo> 
void BidirectionalPathFinder<PointInfo, CellType, CostInfo>::
ToOutputCurrentState()
{
	_pathFinderStart->ToOutputCurrentState();
	_pathFinderGoal->ToOutputCurrentState();
	
}

#endif
