//
// Created by Marco Müllner on 08.01.18.
//

#include "rk4body.h"

RK4Body::RK4Body(MVector initial_position, MVector initial_velocity, double mass)
        : IBody(initial_position, initial_velocity, mass, "RK4")
{
}

MVector RK4Body::computeNextVelocity()
{
    m_nextVelocity = getVelocity(eI_0) + timeStep*(getAcceleration(eI_1) + 2*getAcceleration(eI_2) + 2*getAcceleration(eI_3) + getAcceleration(eI_4))/6;
    return m_nextVelocity;
}

MVector RK4Body::computeNextPosition()
{
    m_nextPosition = getPosition(eI_0) + timeStep*(getVelocity(eI_1) + 2*getVelocity(eI_2) + 2*getVelocity(eI_3) + getAcceleration(eI_4))/6;
    return m_nextPosition;
}

void RK4Body::computeK1(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eI_0),eI_1);
    setVelocity(getVelocity(eI_0),eI_1);

    setPosition(getPosition(eI_0)+getVelocity(eI_1)*timeStep/2,eI_1);
}

void RK4Body::computeK2(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eI_1),eI_2);
    setVelocity(getVelocity(eI_0) + getVelocity(eI_1)*timeStep/2,eI_2);

    setPosition(getPosition(eI_0) + getVelocity(eI_2)*timeStep/2,eI_2);
}

void RK4Body::computeK3(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eI_2),eI_3);
    setVelocity(getVelocity(eI_0) + getVelocity(eI_2)*timeStep/2,eI_3);

    setPosition(getPosition(eI_0) + getVelocity(eI_3)*timeStep/2,eI_3);
}

void RK4Body::computeK4(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eI_3),eI_4);
    setVelocity(getVelocity(eI_0) + getVelocity(eI_3)*timeStep/2,eI_4);
}