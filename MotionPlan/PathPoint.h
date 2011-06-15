#pragma once

struct PathPoint
{
public:
	int Index;
	float Rank;

	//Overload the < operator.
	bool operator< ( const PathPoint &point2);

	//Overload the > operator.
	bool operator> ( const PathPoint &point2);

	PathPoint();
	~PathPoint();
};

//Overload the < operator.
bool operator< (const PathPoint &point1, const PathPoint &point2);
//Overload the > operator.
bool operator> (const PathPoint &point1, const PathPoint &point2);