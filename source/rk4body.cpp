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
    MVector k1 = m_curr_acceleration;
}

MVector RK4Body::computeNextPosition()
{

}