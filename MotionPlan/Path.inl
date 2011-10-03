#ifndef MOTIONPLAN_ASTAR_PATH_H
#error "Include from BasePathFinder.h only."
#else

template<typename PointInfo>
Path<PointInfo>::Path(std::vector<PointInfo> points)
{
	_points = points;
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
	return  new Path<PointInfo>(std::vector<PointInfo>());
}

template<typename PointInfo>
PointInfo Path<PointInfo>::GetPoint(int index)
{
	PointInfo result;
	if ((index<_points.size()) && (index >= 0))
	{
		result = _points[index];
	}
	else
	{
		if (index<0)
		{
			result = _points[0];
		}
		else
		{
			result = _points.back();
		}

	}
	return result;
}

template<typename PointInfo>
int Path<PointInfo>::Count()
{
	return _points.size();
}

template<typename PointInfo>
void Path<PointInfo>::AddPoints(std::vector<PointInfo>& points)
{
	//_points.resize(_points.size() + points.size()+1);
	for (std::vector<PointInfo>::iterator it = points.begin(); it != points.end(); ++it)
	{
		_points.push_back(*it);
	}

}

#endif
