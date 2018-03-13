//
// Created by marco on 05.12.17.
//
#include "implementations/eulerbody.h"

EulerBody::EulerBody(MVector initial_position, MVector initial_velocity, double mass)
        : IBody(initial_position, initial_velocity, mass, "Euler")
{
}

void EulerBody::computeNextStep(vector<EulerBody> bodies)
{
    setAcceleration(computeAcceleration<vector<EulerBody>::iterator>(bodies.begin(),bodies.end()));
    m_nextVelocity = computeNextVelocity();
    m_nextPosition = computeNextPosition();
}

MVector EulerBody::computeNextVelocity()
{
    return getVelocity() + getAcceleration()*timeStep;
}

MVector EulerBody::computeNextPosition()
{
    return getPosition() + getVelocity()*timeStep;
}
