//
// Created by marco on 09.01.18.
//

#ifndef NBODYSOLVER_LEAPFROGBODY_H
#define NBODYSOLVER_LEAPFROGBODY_H

#include "ibody.h"

using namespace std;

class LeapfrogBody : public IBody
{
public:
    LeapfrogBody(MVector initial_position,MVector initial_velocity, double mass);

    void computeCurrentAcceleration(vector<LeapfrogBody> bodies);
    void computeNextAcceleration(vector<LeapfrogBody> bodies);
private:
    LeapfrogBody() = default;

    MVector computeNextVelocity() override;
    MVector computeNextPosition() override;
};

#endif //NBODYSOLVER_LEAPFROGBODY_H
