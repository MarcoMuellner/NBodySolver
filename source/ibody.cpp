//
// Created by Marco Müllner on 08.01.18.
//
#include "ibody.h"
#include <math.h>
#include <stdexcept>
#include <iostream>

int IBody::m_prevID = 0;

IBody::IBody(MVector &initial_position, MVector &initial_velocity, const double &mass, const string algorithmName)
        :m_mass(mass)
        ,m_id(m_prevID+1)
        ,m_algorithm(algorithmName)
{
    setPosition(initial_position);
    setVelocity(initial_velocity);

    setAcceleration(MVector().zeros(initial_position.size()));

    m_nextPosition.zeros(initial_position.size());
    m_nextVelocity.zeros(initial_velocity.size());
    m_nextAcceleration.zeros(initial_velocity.size());

    m_prevID = m_id;

    m_positionList.push_back(initial_position);
}

MVector IBody::getPosition(const ePosID posID)
{
    if(m_position.size() > (int)posID)
    {
        return m_position[posID];
    }
    else
    {
        throw logic_error("The posID you input doesn't exist");
    }
}

MVector IBody::getVelocity(const ePosID posID)
{
    MVector retVal;
    if(m_velocity.size() > (int)posID)
    {
        retVal =  m_velocity[posID];
    }
    else
    {
        throw logic_error("The posID you input doesn't exist");
    }

    return retVal;
}

MVector IBody::getAcceleration(const ePosID posID)
{
    if(m_acceleration.size() > (int)posID)
    {
        return m_acceleration[posID];
    }
    else
    {
        throw logic_error("The posID you input doesn't exist");
    }
}

MVector IBody::getPreviousPosition(const int id)
{
    int realID = m_positionList.size() + id;
    if(!m_positionList.empty() && id < 0 && realID > 0)
    {
        return m_positionList[realID];
    }
    else if (!m_positionList.empty())
    {
        return m_positionList.back();
    }
    else
    {
        throw logic_error("PositionList appears to be empty! You cannot access it without setting something first");
    }
}

void IBody::setPosition(const MVector &value, const ePosID posID)
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
}

void IBody::setVelocity(const MVector &value, const ePosID posID)
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

void IBody::setAcceleration(const MVector &value, const ePosID posID)
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

MVector IBody::computeGravity(const MVector &otherPosition, const double otherMass)
{
    return -G*otherMass*(getPosition() - otherPosition)/pow(((getPosition() - otherPosition).abs()+sigma),3);
}

void IBody::applyChanges()
{
    setPosition(m_nextPosition);
    setVelocity(m_nextVelocity);

    if((m_positionList.size()-1)%100 == 0)
    {
        cout << m_algorithm << ",It:" << m_positionList.size()-1<<" Object"<< m_id << " pos " << getPosition().toString() << endl;
    }

    m_positionList.push_back(m_nextPosition);
}
