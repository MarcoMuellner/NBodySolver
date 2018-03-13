//
// Created by Marco Müllner on 08.01.18.
//

#ifndef NBODYSOLVER_RK4BODY_H
#define NBODYSOLVER_RK4BODY_H

#include "support/ibody.h"

class RK4Body :public IBody
{
public:
    RK4Body(MVector initial_position, MVector initial_velocity, double mass);
    MVector computeNextVelocity() override;
    MVector computeNextPosition() override;

    void computeK1(vector<RK4Body> bodies);
    void computeK2(vector<RK4Body> bodies);
    void computeK3(vector<RK4Body> bodies);
    void computeK4(vector<RK4Body> bodies);
private:
    RK4Body() = default;

};

#endif //NBODYSOLVER_RK4BODY_H