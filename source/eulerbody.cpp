//
// Created by marco on 05.12.17.
//
#include "eulerbody.h"

EulerBody::EulerBody(MVector initial_position, MVector initial_velocity, double mass)
        :IBody(initial_position,initial_velocity,mass)
{
}

void EulerBody::computeNextStep(vector<EulerBody> bodies)
{
    m_nextVelocity = computeNextVelocity();
    m_nextPosition = computeNextPosition();
    m_nextAcceleration = computeAcceleration<vector<EulerBody>::iterator>(bodies.begin(),bodies.end());
}

MVector EulerBody::computeNextVelocity()
{
    return getVelocity() + getAcceleration()*timeStep;
}

MVector EulerBody::computeNextPosition()
{
    return getPosition() + getVelocity()*timeStep;
}
