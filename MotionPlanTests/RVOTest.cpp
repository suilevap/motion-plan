#include "gtest/gtest.h"
#include "RVOInterface.h"


TEST(RVO, BaseTest)
{
    RVO_Start(30, 196, 9, 30 * 6, 40* 5);
    RVO_SetCellMapRegion(10, 10, 5, 5);
    RVO_ProcessObstacles();
    double agent1 = RVO_AddAgent(4, 1);
    double agent2 = RVO_AddAgent(4, 1);
    RVO_UpdateAgent(agent1, 5, 5, 0.2, 0.2);
    RVO_UpdateAgent(agent2, 20, 20, -0.2, -0.2);
    RVO_Update();

    double vx1 = RVO_GetAgentSpeedX(agent1);
    double vy1 = RVO_GetAgentSpeedY(agent1);

    double v2 = RVO_GetAgentSpeedX(agent2);

}

//DllExport double RVO_SetCellMapRegion(double x0, double y0, double w, double h);
//DllExport double RVO_ProcessObstacles();
//DllExport double RVO_AddAgent(double radius, double maxSpeed);
//DllExport double RVO_UpdateAgent(double agentId, double x, double y, double xspeed, double yspeed);
//DllExport double RVO_GetAgentSpeed(double agentId, double root);
//DllExport double RVO_Update();
//DllExport double RVO_Start(double timeStep, double neighborDist, double maxNeighbors, double timeHorizon, double timeHorizonObst);
