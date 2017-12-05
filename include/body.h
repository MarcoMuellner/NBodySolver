//
// Created by marco on 05.12.17.
//

#ifndef NBODYSOLVER_BODY_H
#define NBODYSOLVER_BODY_H

#include "mvector.h"
using namespace std;

class Body
{
public:
    Body(MVector initial_position, MVector initial_velocity, double mass);
    ~Body() = default;

    void computeNextStep(vector<MVector> otherPositions, vector<double> otherMasses);
    MVector getPosition(){return m_curr_position;}
    double getMass(){return m_mass;}

private:
    Body() = default;

    MVector computeAcceleration(const MVector otherPosition, const double otherMass);
    MVector computeVelocity();
    MVector computePosition();

    MVector m_curr_position;
    MVector m_curr_velocity;
    MVector m_curr_acceleration;
    double m_mass;
    vector< MVector > m_positionList;

};

#endif //NBODYSOLVER_BODY_H
