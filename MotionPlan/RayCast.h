#pragma once
#ifndef MOTIONPLAN_RAYCAST_H_
#define MOTIONPLAN_RAYCAST_H_

#include "DllExport.h"

class DllExportCpp RayCast
{
protected:
	void Bresenham(int x1, int y1, int x2, int y2);
public:
	void Execute(int x1, int y1, int x2, int y2);

	virtual bool HandlePoint(int x, int y) = 0;
};

#endif//MOTIONPLAN_RAYCAST_H_
