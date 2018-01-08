//
// Created by Marco Müllner on 08.01.18.
//
#include "ibody.h"
#include <math.h>

int IBody::m_prevID = 0;

IBody::IBody(MVector initial_position, MVector initial_velocity, double mass)
        :m_id(m_prevID+1)
{
    m_curr_position = initial_position;
    m_curr_velocity = initial_velocity;
    m_curr_acceleration.zeros(m_curr_position.size());
    m_mass = mass;
    m_prevID = m_id;

    m_positionList.push_back(m_curr_position);
}

void IBody::computeNextStep(vector<IBody>::iterator beginIt,vector<IBody>::iterator endIt)
{
    m_nextVelocity = computeNextVelocity();
    m_nextPosition = computeNextPosition();
    m_nextAcceleration = computeAcceleration(beginIt,endIt);
}

MVector IBody::computeAcceleration(vector<IBody>::iterator beginIt,vector<IBody>::iterator endIt)
{
    MVector nextAcceleration;
    nextAcceleration.zeros(m_curr_velocity.size());

    while(beginIt != endIt)
    {
        if(m_id != beginIt->getID())
        {
            nextAcceleration += computeGravity(beginIt->getPosition(),beginIt->getMass());
        }
        ++beginIt;
    }
    return nextAcceleration;
}

MVector IBody::computeGravity(const MVector otherPosition, const double otherMass)
{
    return -G*otherMass*(m_curr_position - otherPosition)/pow((m_curr_position - otherPosition).abs(),3);
}

void IBody::applyChanges()
{
    m_curr_position = m_nextPosition;
    m_curr_velocity = m_nextVelocity;
    m_curr_acceleration = m_nextAcceleration;

    printf("Object %d, abs pos %lf\n",m_id,m_curr_position.abs());

    m_positionList.push_back(m_curr_position);
}
