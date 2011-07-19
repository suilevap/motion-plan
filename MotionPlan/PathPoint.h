#pragma once

struct PathPoint
{

public:
	int Index;
	float Distance;
	float EstimateDistance;
	float Rank;


	//Overload the < operator.
	bool operator< ( const PathPoint &point2);

	//Overload the > operator.
	bool operator> ( const PathPoint &point2);

	PathPoint(int index, float distance, float estimateDistance);
	PathPoint();
	~PathPoint();
};

//Overload the < operator.
bool operator< (const PathPoint &point1, const PathPoint &point2);
//Overload the > operator.
bool operator> (const PathPoint &point1, const PathPoint &point2);