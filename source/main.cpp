#include <cstdio>
#include "body.h"
#include "mvector.h"

using namespace std;

int main(int argc, char *argv[])
{
    vector<double> b1InitPos = {-10,10};
    vector<double> b1InitVel = {-10,10};
    Body b1(MVector(b1InitPos),MVector(b1InitVel),10);

    vector<double> b2InitPos = {20,-20};
    vector<double> b2InitVel = {20,-20};
    Body b2(MVector(b2InitPos),MVector(b2InitVel),10);
    vector<double> mass;
    mass.push_back(10);

    for (int i = 0;i <= 5;i++)
    {
        vector<MVector> b1Pos;
        b1Pos.push_back(b2.getPosition());
        vector<MVector> b2Pos;
        b2Pos.push_back(b1.getPosition());

        b1.computeNextStep(b1Pos,mass);
        b2.computeNextStep(b2Pos,mass);

        printf("Pos1: %lf\n",b1.getPosition().abs());
        printf("Pos2: %lf\n",b2.getPosition().abs());
    }

    return 1;
}