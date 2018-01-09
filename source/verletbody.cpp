//
// Created by marco on 09.01.18.
//
#include "verletbody.h"
#include <math.h>

VerletBody::VerletBody(MVector initial_position, MVector initial_velocity, double mass)
    :IBody(initial_position,initial_velocity,mass)
{
}


void VerletBody::computeFirstStep(vector<VerletBody> bodies)
{
    setAcceleration(computeAcceleration<vector<VerletBody>::iterator>(bodies.begin(),bodies.end()),eI_0);
    m_nextPosition = getPosition()+getVelocity()*timeStep + pow(timeStep,2)*getAcceleration()/2;
    m_nextVelocity = (m_nextPosition - getPosition())/timeStep;
}

void VerletBody::computeNextStep(vector<VerletBody> bodies)
{
    setAcceleration(computeAcceleration<vector<VerletBody>::iterator>(bodies.begin(),bodies.end()),eI_0);
    m_nextPosition = computeNextPosition();
    m_nextVelocity = computeNextVelocity();
}

MVector VerletBody::computeNextPosition()
{
    return 2*getPosition() -getPreviousPosition(-1)+getAcceleration()*pow(timeStep,2);
}

MVector VerletBody::computeNextVelocity()
{
    return (m_nextPosition - getPosition())/timeStep;
}


