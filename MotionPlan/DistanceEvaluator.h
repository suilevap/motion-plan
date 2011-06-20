#pragma once

#include <math.h>

class DistanceEvaluator
{
public:
	float inline static EuclideanDistance(float x1, float y1, float x2, float y2)
	{
		return (float) sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
	}
};
