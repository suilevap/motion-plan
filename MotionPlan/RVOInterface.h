#pragma once
#include "DllExport.h"

//RVO
DllExport double RVO_SetCellMapRegion(double x0, double y0, double w, double h);
DllExport double RVO_ProcessObstacles();
DllExport double RVO_AddAgent(double radius, double maxSpeed);
DllExport double RVO_UpdateAgent(double agentId, double x, double y, double xspeed, double yspeed);
DllExport double RVO_GetAgentSpeedX(double agentId);
DllExport double RVO_GetAgentSpeedY(double agentId);
DllExport double RVO_Update();
DllExport double RVO_Start(double timeStep, double neighborDist, double maxNeighbors, double timeHorizon, double timeHorizonObst);
