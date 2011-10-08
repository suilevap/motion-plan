#include "stdafx.h"

#include "RVO.h"

#include <vector>

#ifdef USE_GMAPI
#define GMAPI_NO_D3D
#include "gmapi.h"
#endif

#include "RVOInterface.h"

RVO::RVOSimulator sim;

//struct RVO_GM_Obj
//{
//    int RVOObj;
//    int GMObj;
//    RVO_GM_Obj(int rvoObj, int gmObj):
//        RVOObj(rvoObj), GMObj(gmObj)
//    {
//    }
//};

std::vector<int> gmObjects;



double RVO_SetCellMapRegion(double x0, double y0, double w, double h)
{

    std::vector<RVO::Vector2> vertices;
    vertices.push_back(RVO::Vector2(x0, y0));
    vertices.push_back(RVO::Vector2(x0+w, y0));
    vertices.push_back(RVO::Vector2(x0+w, y0+h));
    vertices.push_back(RVO::Vector2(x0, y0+h));

    sim.addObstacle(vertices);

    return 0;
}

double RVO_ProcessObstacles()
{
    sim.processObstacles();
    return 0;
}

double RVO_AddAgent(double radius, double maxSpeed)
{
    int id = sim.addAgent(RVO::Vector2(0,0));
    sim.setAgentRadius(id, radius);
    sim.setAgentMaxSpeed(id, maxSpeed);
    gmObjects.push_back(id);
    return gmObjects.size()-1;
}

double RVO_UpdateAgent(double agentId, double x, double y, double xspeed, double yspeed)
{
    int id = gmObjects[(int)agentId];
    sim.setAgentPosition(id, RVO::Vector2(x, y));
    sim.setAgentPrefVelocity(id, RVO::Vector2(xspeed, yspeed));
    return 0;
}

double RVO_GetAgentSpeedX(double agentId)
{
    int id = gmObjects[(int)agentId];
    const RVO::Vector2& v = sim.getAgentVelocity(id);
    return v.x();
}
double RVO_GetAgentSpeedY(double agentId)
{
    int id = gmObjects[(int)agentId];
    const RVO::Vector2& v = sim.getAgentVelocity(id);
    return v.y();
}

double RVO_Update()
{
    sim.doStep();
    return 0;
}

double RVO_Start(double timeStep, double neighborDist, double maxNeighbors, double timeHorizon, double timeHorizonObst)
{
    sim.setTimeStep(timeStep);
    sim.setAgentDefaults(neighborDist, (int)maxNeighbors, timeHorizon, timeHorizonObst, 1, 1);
    return 0;
}

