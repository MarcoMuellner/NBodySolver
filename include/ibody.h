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
        eI_0 = 0,
        eI_1 = 1,
        eI_2 = 2,
        eI_3 = 3,
        eI_4 = 4,
    };
    IBody(MVector initial_position, MVector initial_velocity, double mass);
    ~IBody() = default;

    MVector getPosition(ePosID posID = eI_0);
    MVector getVelocity(ePosID posID = eI_0);
    MVector getAcceleration(ePosID posID = eI_0);
    double getMass() const {return m_mass;};
    vector<MVector> getPositionHistory(){return m_positionList;};
    MVector getPreviousPosition(int id=0);

    void applyChanges();

    int getID() const {return m_id;}
    static void resetID(){m_prevID = 0;};
protected:
    IBody() = default;
    virtual MVector computeNextVelocity() = 0;
    virtual MVector computeNextPosition() = 0;

    void setVelocity(MVector value,ePosID posID = eI_0);
    void setPosition(MVector value,ePosID posID = eI_0);
    void setAcceleration(MVector value,ePosID posID = eI_0);

    template<typename RandomAccessIterator>
    MVector computeAcceleration(RandomAccessIterator beginIt,RandomAccessIterator endIt,ePosID posID = eI_0)
    {
        MVector nextAcceleration;
        nextAcceleration.zeros(getAcceleration().size());

        while(beginIt != endIt)
        {
            if(m_id != beginIt->getID())
            {
                nextAcceleration = nextAcceleration + computeGravity(beginIt->getPosition(posID),beginIt->getMass());
            }
            ++beginIt;
        }
        return nextAcceleration;
    }

    MVector computeGravity(const MVector otherPosition, const double otherMass);

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
