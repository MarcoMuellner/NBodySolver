//
// Created by Marco Müllner on 08.01.18.
//

#ifndef NBODYSOLVER_RK4BODY_H
#define NBODYSOLVER_RK4BODY_H

#include "ibody.h"

class RK4Body :public IBody
{
public:
    RK4Body(MVector initial_position, MVector initial_velocity, double mass);
    MVector computeNextVelocity() override;
    MVector computeNextPosition() override;

    void computeK1(vector<IBody>::iterator beginIt, vector<IBody>::iterator endIt);
    void computeK2(vector<IBody>::iterator beginIt, vector<IBody>::iterator endIt);
    void computeK3(vector<IBody>::iterator beginIt, vector<IBody>::iterator endIt);
    void computeK4(vector<IBody>::iterator beginIt, vector<IBody>::iterator endIt);
private:
    RK4Body() = default;

};

#endif //NBODYSOLVER_RK4BODY_H
