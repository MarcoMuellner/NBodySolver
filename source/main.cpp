#include <cstdio>
#include "eulerbody.h"
#include "rk4body.h"

using namespace std;

void runEuler(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{
    vector<EulerBody> bodies;
    if (initPos.size() == initVel.size() && initVel.size() == mass.size())
    {
        auto itInitPos = initPos.begin();
        auto itInitVel = initVel.begin();
        auto itMass = mass.begin();

        while(itInitPos != initPos.end() && itInitVel != initVel.end() && itMass != mass.end())
        {
            bodies.emplace_back(EulerBody(MVector(*itInitPos),MVector(*itInitVel),*itMass));
            ++itInitPos;
            ++itInitVel;
            ++itMass;
        }
    }

    for (int i = 0;i<=iterations;++i)
    {
        auto itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeNextStep(bodies.begin(),bodies.end());
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->applyChanges();
            ++itBodies;
        }
    }
}

void runRK4(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{
    vector<RK4Body> bodies;
    if (initPos.size() == initVel.size() && initVel.size() == mass.size())
    {
        auto itInitPos = initPos.begin();
        auto itInitVel = initVel.begin();
        auto itMass = mass.begin();

        while(itInitPos != initPos.end() && itInitVel != initVel.end() && itMass != mass.end())
        {
            bodies.emplace_back(RK4Body(MVector(*itInitPos),MVector(*itInitVel),*itMass));
            ++itInitPos;
            ++itInitVel;
            ++itMass;
        }
    }
    for (int i = 0;i<=iterations;++i)
    {
        auto itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK1(bodies.begin(),bodies.end());
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK2(bodies.begin(),bodies.end());
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK3(bodies.begin(),bodies.end());
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK4(bodies.begin(),bodies.end());
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeNextVelocity();
            itBodies->computeNextPosition();
            itBodies->applyChanges();
            ++itBodies;
        }
    }
}

int main(int argc, char *argv[])
{
    vector<double> b1InitPos = {-10,10};
    vector<double> b1InitVel = {-10,10};


    vector<double> b2InitPos = {10,-10};
    vector<double> b2InitVel = {10,-10};

    vector<double> b3InitPos = {0,-10};
    vector<double> b3InitVel = {0,-10};

    vector<double> mass = {10,10,10};
    vector<vector<double> > initPositions = {b1InitPos,b2InitPos,b3InitPos};
    vector<vector<double> > initVel = {b1InitVel,b2InitVel,b3InitVel};
    //runEuler(initPositions,initVel,mass);
    runRK4(initPositions,initVel,mass);

    return 1;
}