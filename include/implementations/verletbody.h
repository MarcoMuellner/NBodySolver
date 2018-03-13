//
// Created by marco on 09.01.18.
//

#ifndef NBODYSOLVER_VERLETBODY_H_H
#define NBODYSOLVER_VERLETBODY_H_H

#include "ibody.h"

using namespace std;

class VerletBody : public IBody
{
public:
    VerletBody(MVector initial_position,MVector initial_velocity, double mass);
    void computeFirstStep(vector<VerletBody> bodies);
    void computeNextStep(vector<VerletBody> bodies);
private:
    VerletBody() = default;

    MVector computeNextVelocity() override;
    MVector computeNextPosition() override;
};

#endif //NBODYSOLVER_VERLETBODY_H_H
