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
private:
    RK4Body() = default;

    MVector computeNextVelocity() override;
    MVector computeNextPosition() override ;
};

#endif //NBODYSOLVER_RK4BODY_H
