//
// Created by Marco Müllner on 08.01.18.
//

#ifndef NBODYSOLVER_IBODY_H
#define NBODYSOLVER_IBODY_H

#include "mvector.h"
#include "defines.h"
#include <list>

using namespace std;

class IBody
{
public:
    enum ePosID
    {
        eCurr = 0,
        eK1 = 1,
        eK2 = 2,
        eK3 = 3,
        eK4 = 4,
    };
    IBody(MVector initial_position, MVector initial_velocity, double mass);
    ~IBody() = default;

    virtual void computeNextStep(vector<IBody>::iterator beginIt,vector<IBody>::iterator endIt);
    MVector getPosition(ePosID posID = eCurr);
    MVector getVelocity(ePosID posID = eCurr);
    MVector getAcceleration(ePosID posID = eCurr);
    void setVelocity(MVector value,ePosID posID = eCurr);
    void setPosition(MVector value,ePosID posID = eCurr);
    void setAcceleration(MVector value,ePosID posID = eCurr);
    double getMass() const {return m_mass;};
    void applyChanges();

protected:
    IBody() = default;
    virtual MVector computeNextVelocity() = 0;
    virtual MVector computeNextPosition() = 0;
    MVector computeAcceleration(vector<IBody>::iterator beginIt, vector<IBody>::iterator endIt, ePosID posID = eCurr);
    MVector computeGravity(const MVector otherPosition, const double otherMass);
    int getID() const {return m_id;}

    vector<MVector> m_position;
    vector<MVector> m_velocity;
    vector<MVector> m_acceleration;

    MVector m_nextVelocity;
    MVector m_nextPosition;
    MVector m_nextAcceleration;

    double m_mass;
    vector< MVector > m_positionList;

    const int m_id;
    static int m_prevID;
};

#endif //NBODYSOLVER_IBODY_H
