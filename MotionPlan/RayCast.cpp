#include "stdafx.h"

#include "RayCast.h"

void RayCast::Execute(int x1, int y1, int x2, int y2)
{
	Bresenham(x1, y1, x2, y2);
}

void RayCast::Bresenham(int x1, int y1, int x2, int y2)
{
	bool stoped;
    signed char ix;
    signed char iy;
 
    // if x1 == x2 or y1 == y2, then it does not matter what we set here
    int delta_x((x2 > x1?(ix = 1, x2 - x1):(ix = -1, x1 - x2)) << 1);
    int delta_y((y2 > y1?(iy = 1, y2 - y1):(iy = -1, y1 - y2)) << 1);
 
    stoped = HandlePoint(x1, y1);
	if (stoped)
	{
		return;
	}
 
    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));
 
        while (x1 != x2)
        {
            if (error >= 0)
            {
                if (error || (ix > 0))
                {
                    y1 += iy;
                    error -= delta_x;
                }
                // else do nothing
            }
            // else do nothing
 
            x1 += ix;
            error += delta_y;
 
            stoped = HandlePoint(x1, y1);
			if (stoped)
			{
				break;
			}
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));
 
        while (y1 != y2)
        {
            if (error >= 0)
            {
                if (error || (iy > 0))
                {
                    x1 += ix;
                    error -= delta_y;
                }
                // else do nothing
            }
            // else do nothing
 
            y1 += iy;
            error += delta_x;
 
            stoped = HandlePoint(x1, y1);
			if (stoped)
			{
				break;
			}
        }
    }
}