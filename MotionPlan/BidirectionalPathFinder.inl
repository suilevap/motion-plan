#ifndef MOTIONPLAN_ASTAR_BIDIRECTIONALPATHFINDER_H
#error "Include from BidirectionalPathFinder.h only."
#else

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal> 
BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
BidirectionalPathFinder(MapView<PointInfo, CellType, CostInfo>* map)
{
	Init(map);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
~BidirectionalPathFinder()
{
	delete _pathFinderStart;
	delete _pathFinderGoal;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
void BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
Init(MapView<PointInfo, CellType, CostInfo>* map)
{
    _map = map;
	_pathFinderStart = new AStar::BasePathFinder<PointInfo, CellType, CostInfo, CellQueueStart>(_map);
	_pathFinderGoal = new AStar::BasePathFinder<PointInfo, CellType, CostInfo, CellQueueGoal>(_map);
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
void BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
FindStart(PointInfo start, PointInfo goal)
{
	_pathFinderStart->FindStart(start, goal);
	_pathFinderGoal->FindStart(goal, start);
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
int BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
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
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
bool BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
IsGoal(NodeInfo node)
{
	bool result = (_pathFinderGoal->FindIsPathExists(node));
	return result;
}

template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
bool BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
FindIsPathExists(NodeInfo node)
{
	bool result = (_pathFinderStart->FindIsPathExists(node));
	return result;
}


template<
	typename PointInfo, 
	typename CellType, 	
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
Path<PointInfo>* BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
FindEnd(PointInfo point)
{
	Path<PointInfo>* result;
	if (FindIsPathExists(_map->GetNode(point)))
	{
		Path<PointInfo>* path1 = _pathFinderStart->FindEnd(point);
		Path<PointInfo>* path2 = _pathFinderGoal->FindEnd(point);
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
	typename CostInfo,
	typename CellQueueStart,
	typename CellQueueGoal>
void BidirectionalPathFinder<PointInfo, CellType,CostInfo, CellQueueStart, CellQueueGoal>::
ToOutputCurrentState()
{
	_pathFinderStart->ToOutputCurrentState();
	_pathFinderGoal->ToOutputCurrentState();
	
}

#endif
