//
// Created by Marco Müllner on 08.01.18.
//
#include "ibody.h"
#include <math.h>
#include <stdexcept>

int IBody::m_prevID = 0;

IBody::IBody(MVector initial_position, MVector initial_velocity, double mass)
        :m_id(m_prevID+1)
{
    setPosition(initial_position);
    setVelocity(initial_velocity);

    setAcceleration(MVector().zeros(initial_position.size()));
    m_mass = mass;
    m_prevID = m_id;

    m_positionList.push_back(initial_position);
}

MVector IBody::getPosition(ePosID posID)
{
    if(m_position.size() > (int)posID)
    {
        return m_position[posID];
    }
}

MVector IBody::getVelocity(ePosID posID)
{
    if(m_velocity.size() > (int)posID)
    {
        return m_velocity[posID];
    }
}

MVector IBody::getAcceleration(ePosID posID)
{
    if(m_acceleration.size() > (int)posID)
    {
        return m_acceleration[posID];
    }
}

void IBody::setPosition(MVector value,ePosID posID)
{
    if(m_position.size() > (int)posID)
    {
        m_position[posID] = value;
    }
    else if(m_position.size() == posID)
    {
        m_position.push_back(value);
    }
    else
    {
        throw logic_error("You need to set previous position values before you can add one after that");
    }
    return;
}

void IBody::setVelocity(MVector value,ePosID posID)
{
    if(m_velocity.size() > (int)posID)
    {
        m_velocity[posID] = value;
    }
    else if(m_velocity.size() == posID)
    {
        m_velocity.push_back(value);
    }
    else
    {
        throw logic_error("You need to set previous position values before you can add one after that");
    }
}

void IBody::setAcceleration(MVector value,ePosID posID)
{
    if(m_acceleration.size() > (int)posID)
    {
        m_acceleration[posID] = value;
    }
    else if(m_acceleration.size() == posID)
    {
        m_acceleration.push_back(value);
    }
    else
    {
        throw logic_error("You need to set previous position values before you can add one after that");
    }
}

void IBody::computeNextStep(vector<IBody>::iterator beginIt,vector<IBody>::iterator endIt)
{
    m_nextVelocity = computeNextVelocity();
    m_nextPosition = computeNextPosition();
    m_nextAcceleration = computeAcceleration(beginIt,
                                             endIt);
}

MVector IBody::computeAcceleration(vector<IBody>::iterator beginIt, vector<IBody>::iterator endIt, ePosID posID)
{
    MVector nextAcceleration;
    nextAcceleration.zeros(getAcceleration().size());

    while(beginIt != endIt)
    {
        if(m_id != beginIt->getID())
        {
            nextAcceleration += computeGravity(beginIt->getPosition(posID),beginIt->getMass());
        }
        ++beginIt;
    }
    return nextAcceleration;
}

MVector IBody::computeGravity(const MVector otherPosition, const double otherMass)
{
    return -G*otherMass*(getPosition() - otherPosition)/pow((getPosition() - otherPosition).abs(),3);
}

void IBody::applyChanges()
{
    setPosition(m_nextPosition);
    setVelocity(m_nextVelocity);
    setAcceleration(m_nextAcceleration);

    printf("Object %d, abs pos %lf\n",m_id,getPosition().abs());

    m_positionList.push_back(m_nextPosition);
}
