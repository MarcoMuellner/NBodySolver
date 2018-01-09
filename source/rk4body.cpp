//
// Created by Marco Müllner on 08.01.18.
//

#include "rk4body.h"

RK4Body::RK4Body(MVector initial_position, MVector initial_velocity, double mass)
        :IBody(initial_position,initial_velocity,mass)
{
}

MVector RK4Body::computeNextVelocity()
{
    m_nextVelocity = getVelocity(eCurr) + timeStep*(getAcceleration(eK1) + 2*getAcceleration(eK2) + 2*getAcceleration(eK3) + getAcceleration(eK4))/6;
    return m_nextVelocity;
}

MVector RK4Body::computeNextPosition()
{
    m_nextPosition = getPosition(eCurr) + timeStep*(getVelocity(eK1) + 2*getVelocity(eK2) + 2*getVelocity(eK3) + getAcceleration(eK4))/6;
    return m_nextPosition;
}

void RK4Body::computeK1(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eCurr),eK1);
    setVelocity(getVelocity(eCurr),eK1);

    setPosition(getPosition(eCurr)+getVelocity(eK1)*timeStep/2,eK1);
}

void RK4Body::computeK2(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eK1),eK2);
    setVelocity(getVelocity(eCurr) + getVelocity(eK1)*timeStep/2,eK2);

    setPosition(getPosition(eCurr) + getVelocity(eK2)*timeStep/2,eK2);
}

void RK4Body::computeK3(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eK2),eK3);
    setVelocity(getVelocity(eCurr) + getVelocity(eK2)*timeStep/2,eK3);

    setPosition(getPosition(eCurr) + getVelocity(eK3)*timeStep/2,eK3);
}

void RK4Body::computeK4(vector<RK4Body> bodies)
{
    setAcceleration(computeAcceleration<vector<RK4Body>::iterator>(bodies.begin(),bodies.end(),eK3),eK4);
    setVelocity(getVelocity(eCurr) + getVelocity(eK3)*timeStep/2,eK4);
}