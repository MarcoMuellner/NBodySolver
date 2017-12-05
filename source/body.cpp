//
// Created by marco on 05.12.17.
//
#include "body.h"
#include "defines.h"
#include <math.h>
#include <cstdio>

Body::Body(MVector initial_position, MVector initial_velocity, double mass)
{
    m_curr_position = initial_position;
    m_curr_velocity = initial_velocity;
    m_curr_acceleration.zeros(m_curr_position.size());
    m_mass = mass;

    m_positionList.push_back(m_curr_position);
}

void Body::computeNextStep(vector<MVector> otherPositions, vector<double> otherMasses)
{
    MVector nextVelocity = computeVelocity();
    MVector nextPosition = computePosition();
    MVector nextAcceleration;
    nextAcceleration.zeros(nextVelocity.size());

    if (otherPositions.size() == otherMasses.size())
    {
        auto itOtherPos = otherPositions.begin();
        auto itOtherMass = otherMasses.begin();
        while(itOtherPos != otherPositions.end() && itOtherMass != otherMasses.end())
        {
            nextAcceleration += computeAcceleration((*itOtherPos),(*itOtherMass));

            ++itOtherPos;
            ++itOtherMass;
        }
    }

    m_curr_position = nextPosition;
    m_curr_velocity = nextVelocity;
    m_curr_acceleration = nextAcceleration;

    m_positionList.push_back(nextPosition);
}

MVector Body::computeVelocity()
{
    return m_curr_velocity + m_curr_acceleration*timeStep;
}

MVector Body::computePosition()
{
    return m_curr_position + m_curr_velocity*timeStep;
}

MVector Body::computeAcceleration(const MVector otherPosition, const double otherMass)
{
    return -G*otherMass*(m_curr_position - otherPosition)/pow((m_curr_position - otherPosition).abs(),3);
}
