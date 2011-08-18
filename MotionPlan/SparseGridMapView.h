#pragma once
#ifndef MOTIONPLAN_SPARSEGRIDMAPVIEW_H_
#define MOTIONPLAN_SPARSEGRIDMAPVIEW_H_

#include "GridMapView.h"
#include <vector>
#include "Point.h"
#include "EdgeInfo.h"
#include "DistanceEvaluator.h"
//     _

template<class CellType>
class SparseGridMapView :
	public GridMapView<CellType, float>
{
private:
	int* _mapSparse;
	int GetSparseId(int node);
	int GetSparseMainNode(int node);

protected:
	bool IsCellSparse(int node);
	void AddCellSparse(int node);
	void RemoveCellSparse(int node);
	
	void GetNeighborsPartialFromSparsed(
		int nodeNeighboor1, 
		int nodeNeighboor2, 
		std::vector<AStar::EdgeInfo<int,float>>& neighbors, 
		float d, 
		float sparceCellD);
	void GetNeighborsPartialFromNotSparsed(
		int nodeNeighboor1, 
		std::vector<AStar::EdgeInfo<int,float>>& neighbors, 
		float d, 
		float sparceCellD);
public:
	SparseGridMapView(float width, float height, float cellSize);
	//virtual ~SparseGridMapView(void);

	virtual Point<float> GetPoint(int& node);	
	virtual int GetNode(Point<float>& point);

	virtual void GetNeighbors(int& node, std::vector<AStar::EdgeInfo<int,float>>& neighbors);

	virtual void SetCell(int& node, CellType cell);

};

#include "SparseGridMapView.inl"

#endif//MOTIONPLAN_SPARSEGRIDMAPVIEW_H_
