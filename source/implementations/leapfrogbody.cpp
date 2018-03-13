//
// Created by marco on 09.01.18.
//

#include "leapfrogbody.h"
#include <math.h>

LeapfrogBody::LeapfrogBody(MVector initial_position, MVector initial_velocity, double mass)
        : IBody(initial_position, initial_velocity, mass, "Leapfrog")
{
}

MVector LeapfrogBody::computeNextVelocity()
{
    m_nextVelocity = getVelocity(eI_0) + timeStep*(getAcceleration(eI_0)+getAcceleration(eI_1))/2;
    return m_nextVelocity;
}

MVector LeapfrogBody::computeNextPosition()
{
    m_nextPosition = getPosition(eI_0) + getVelocity(eI_0)*timeStep + getAcceleration(eI_0)*pow(timeStep,2)/2;
    return m_nextPosition;
}

void LeapfrogBody::computeCurrentAcceleration(vector<LeapfrogBody> bodies)
{
    setAcceleration(computeAcceleration<vector<LeapfrogBody>::iterator>(bodies.begin(),bodies.end(),eI_0),eI_0);
    setPosition(computeNextPosition(),eI_1);
}

void LeapfrogBody::computeNextAcceleration(vector<LeapfrogBody> bodies)
{
    setAcceleration(computeAcceleration<vector<LeapfrogBody>::iterator>(bodies.begin(),bodies.end(),eI_1),eI_1);
    computeNextVelocity();
}




