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
    return m_curr_velocity + m_curr_acceleration*timeStep;
}

MVector EulerBody::computeNextPosition()
{
    return m_curr_position + m_curr_velocity*timeStep;
}
