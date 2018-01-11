//
// Created by Marco Müllner on 08.01.18.
//

#ifndef NBODYSOLVER_IBODY_H
#define NBODYSOLVER_IBODY_H

#include "mvector.h"
#include "defines.h"
#include <list>

using namespace std;

/**
 * The IBody class represents the basic components of very object. Every implementation of a Body that implements
 * a certain Algorithm to integrate the problem should be derived from this class.
 */
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
    /**
     * This constructor should be the only constructor used within the implementations of the Interface. It sets some
     * basic default variables for position, velocity and acceleration and creates its unique id.
     * @param initial_position r_0 for the position of the body
     * @param initial_velocity v_0 for the velocity of the body
     * @param mass mass of the object
     */
    IBody(MVector &initial_position, MVector &initial_velocity, const double &mass, const string algorithmName);
    ~IBody() = default;

    /**
     * Returns the position of the body. You can set 5 different positions for the current step using setPosition and
     * access these using the posID
     * @param posID an enum, which is used to access one of five different positions of the current Step. Default value
     * is eI_0
     * @return Position of this step.
     */
    MVector getPosition(const ePosID posID = eI_0);
    /**
     * Returns the velocity of the body. You can set 5 different positions for the current step using setVelocity and
     * access these using the posID
     * @param posID an enum, which is used to access one of five different velocities of the current Step. Default value
     * is eI_0
     * @return Velocity of this step.
     */
    MVector getVelocity(const ePosID posID = eI_0);
    /**
     * Returns the acceleration of the body. You can set 5 different positions for the current step using
     * setAcceleration and access these using the posID
     * @param posID an enum, which is used to access one of five different accelerations of the current Step.
     * Default value is eI_0
     * @return Acceleration of this step.
     */
    MVector getAcceleration(const ePosID posID = eI_0);
    /**
     * Returns the mass of the object set through the constructor.
     * @return The mass of the object
     */
    const double getMass() const {return m_mass;};
    /**
     * @return Returns the history of the positions.
     */
    vector<MVector> getPositionHistory(){return m_positionList;};
    /**
     * Returns a specific position.
     * @param id Specify from 0 to -inf. 0 is the current position.
     * @return Returns a specific positions.
     */
    MVector getPreviousPosition(const int id = 0);

    /**
     * Applies the two variables nextVelocity and nextPosition as the current position and adds the position to the
     * history
     */
    void applyChanges();

    /**
     * @return Returns a unique id for each object.
     */
    const int getID() {return m_id;}
    /**
     * Resets the object id to 0
     */
    static void resetID(){m_prevID = 0;};
protected:
    IBody() = default;
    /**
     * Interface functions to compute the next velocity
     * @return Returns the next velocity
     */
    virtual MVector computeNextVelocity() = 0;
    /**
     * Interface functions to compute the next position
     * @return Returns the next position
     */
    virtual MVector computeNextPosition() = 0;

    /**
     * Sets the current velocity for a specific posID. 5 possible values for the current velocity.
     * @param value Value for the velocity
     * @param posID enum for the positionID.
     */
    void setVelocity(const MVector &value, const ePosID posID = eI_0);
    /**
     * Sets the current position for a specific posID. 5 possible values for the current position.
     * @param value Value for the position
     * @param posID enum for the positionID
     */
    void setPosition(const MVector &value, const ePosID posID = eI_0);
    /**
     * Sets the current acceleration for a specific posID. 5 possible values for the current acceleration.
     * @param value Value for the acceleration.
     * @param posID enum for the positionID
     */
    void setAcceleration(const MVector &value, const ePosID posID = eI_0);

    /**
     * The computeAcceleration method computes the acceleration for a specific body. It takes two iterators of objects
     * derived form this class and calculates each accleration for every object.
     * @tparam RandomAccessIterator Template parameter -> classtype of the derived class
     * @param beginIt startIterator
     * @param endIt endIterator
     * @param posID defines which posID is used. Will use the same for each object
     * @return the acceleration vector for this object
     */
    template<typename RandomAccessIterator>
    MVector computeAcceleration(RandomAccessIterator beginIt, RandomAccessIterator endIt, ePosID posID = eI_0)
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

    /**
     * Computes the gravity vector for a given other object
     * @param otherPosition The position of the other object
     * @param otherMass The mass of the other object
     * @return Acceleration vector
     */
    MVector computeGravity(const MVector &otherPosition, const double otherMass);

    vector<MVector> m_position;
    vector<MVector> m_velocity;
    vector<MVector> m_acceleration;

    MVector m_nextVelocity;
    MVector m_nextPosition;
    MVector m_nextAcceleration;

    const double m_mass;
    vector< MVector > m_positionList;

    const int m_id;
    const string m_algorithm;
    static int m_prevID;
};

#endif //NBODYSOLVER_IBODY_H
