//
// Created by marco on 05.12.17.
//
#include "eulerbody.h"

EulerBody::EulerBody(MVector initial_position, MVector initial_velocity, double mass)
        :IBody(initial_position,initial_velocity,mass)
{
}

MVector EulerBody::computeNextVelocity()
{
    return getVelocity() + getAcceleration()*timeStep;
}

MVector EulerBody::computeNextPosition()
{
    return getPosition() + getVelocity()*timeStep;
}
