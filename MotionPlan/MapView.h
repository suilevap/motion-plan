#pragma once

#ifndef MOTIONPLAN_ASTAR_MAPVIEW_H
#define MOTIONPLAN_ASTAR_MAPVIEW_H

#include <vector>
#include "FastVector.h"
#include "EdgeInfo.h"
#include "Path.h"
//#include "Point.h"
#include "DistanceEvaluator.h"

namespace AStar
{

template<
	typename PointInfo, 
	typename CellType, 
	typename CostInfo = float> 
class MapView
{	
protected:
    std::vector<CellType> _map;

public:
	typedef int NodeInfo;
//TODO: create MapView.inl file and move all implementation to it
	virtual void GetNeighbors(NodeInfo node, FastVector<EdgeInfo<NodeInfo,CostInfo>>& neighbors) = 0;
    virtual void GetPointNeighbors(PointInfo point, FastVector<EdgeInfo<NodeInfo,CostInfo>>& neighbors)
    {
        int node = GetNode(point);
        neighbors.clear();
        neighbors.resize(1);
        CostInfo cost = 0;
        neighbors.push_back(EdgeInfo<int,CostInfo>(node, cost));
    }
	virtual PointInfo GetPoint(NodeInfo node)= 0;	
	virtual NodeInfo GetNode(PointInfo& point)= 0;
	virtual NodeInfo GetNodeWrite(PointInfo& point) {return GetNode(point);};

	virtual void SetCellRegion(PointInfo& point, CellType cell, PointInfo& size)= 0;
	virtual PointInfo GetMaxPoint()= 0;
	virtual NodeInfo GetMaxNode()= 0;
	
    virtual Path<PointInfo>* AdjustPath(Path<PointInfo>* path)
    {
        return path;
    }

    inline CostInfo GetCostFromNode(NodeInfo node, PointInfo& point)
    {
        PointInfo nodePoint = GetPoint(node);
        float cost = GetCost(nodePoint, point);
        return cost;
    }
    virtual CostInfo GetCost(PointInfo& p1, PointInfo& p2)
    {
	    float cost = AStar::DistanceEvaluator::EuclideanDistance<float>(p1, p2);
        return cost;
    }
	virtual bool OnMap(PointInfo& point) = 0;

	virtual void ToOutput() = 0;
	
	CellType GetCell(NodeInfo node)
	{
		return _map[node] ;
	}

	void SetCell(NodeInfo node, CellType cell)
	{
		_map[node] = cell;	
	}

	CellType GetCellPoint(PointInfo& point)
	{
		NodeInfo node = GetNode(point);
		CellType cell = GetCell(node);
		return cell;
	}
	void SetCellPoint(PointInfo& point, CellType cell)
	{
		NodeInfo node = GetNodeWrite(point);
		SetCell(node, cell);
	}
	
};

}

#endif //MOTIONPLAN_ASTAR_MAPVIEW_H
