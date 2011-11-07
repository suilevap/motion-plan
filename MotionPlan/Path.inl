#ifndef MOTIONPLAN_ASTAR_PATH_H
#error "Include from BasePathFinder.h only."
#else

template<typename PointInfo>
Path<PointInfo>::Path()
{

}

template<typename PointInfo>
Path<PointInfo>::~Path(void)
{
}

template<typename PointInfo>
std::vector<PointInfo>& Path<PointInfo>::GetPoints()
{
	return _points;
}

template<typename PointInfo>
Path<PointInfo>* Path<PointInfo>::Empty()
{
	//TODO: optimaze
	return new Path<PointInfo>();
}

template<typename PointInfo>
PointInfo Path<PointInfo>::GetPoint(int index)
{
    index = MathHelper::Clamp<int>(index, 0, _points.size()-1);
	PointInfo result = _points[index];
	return result;
}
template<typename PointInfo>
void Path<PointInfo>::SetPoint(int index, PointInfo point)
{
    index = MathHelper::Clamp<int>(index, 0, _points.size()-1);
	_points[index] = point;
}

template<typename PointInfo>
typename Path<PointInfo>::NodeInfo Path<PointInfo>::GetNode(int index)
{
    index = MathHelper::Clamp<int>(index, 0, _points.size()-1);
	NodeInfo result = _nodes[index];
	return result;
}

template<typename PointInfo>
int Path<PointInfo>::Count()
{
	return _points.size();
}

template<typename PointInfo>
void Path<PointInfo>::Reverse()
{
	reverse(_points.begin(), _points.end());
	reverse(_nodes.begin(), _nodes.end());
}


template<typename PointInfo>
void Path<PointInfo>::AddNodes(std::vector<NodeInfo>& nodes)
{
	//_points.resize(_points.size() + points.size()+1);
	for (std::vector<NodeInfo>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		_nodes.push_back(*it);
	}
    
    _points.resize(_nodes.size());

}

template<typename PointInfo>
void Path<PointInfo>::Add(PointInfo point, NodeInfo node)
{
    _nodes.push_back(node);
    _points.push_back(point);
}

#endif
