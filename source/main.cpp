#include <fstream>
#include <iostream>

#include "eulerbody.h"
#include "rk4body.h"
#include "leapfrogbody.h"
#include "verletbody.h"

using namespace std;

template<class T>
vector<T> createBodies(const vector<vector<double> > &initPos,const vector<vector<double> > &initVel,const vector<double> &mass)
{
    IBody::resetID();
    vector<T> bodies;
    if (initPos.size() == initVel.size() && initVel.size() == mass.size())
    {
        auto itInitPos = initPos.begin();
        auto itInitVel = initVel.begin();
        auto itMass = mass.begin();

        while(itInitPos != initPos.end() && itInitVel != initVel.end() && itMass != mass.end())
        {
            bodies.emplace_back(T(MVector(*itInitPos),MVector(*itInitVel),*itMass));
            ++itInitPos;
            ++itInitVel;
            ++itMass;
        }
    }
    return bodies;

}

template<class T>
void savePositionsToFile(vector<T> bodies,string fileName)
{
    for(auto it = bodies.begin();it != bodies.end();++it)
    {
        ofstream out(fileName+"_"+to_string(it->getID())+".txt");

        vector<MVector> values = it->getPositionHistory();
        for(auto valueIt = values.begin();valueIt != values.end();++valueIt)
        {
            out<< valueIt->toString() + "\n";
        }
    }
}

void runEuler(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{
    vector<EulerBody> bodies = createBodies<EulerBody>(initPos,initVel,mass);

    for (int i = 1;i<=iterations;++i)
    {
        auto itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeNextStep(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->applyChanges();
            ++itBodies;
        }
    }
    savePositionsToFile<EulerBody>(bodies,"EulerMethod");
}

void runRK4(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{
    vector<RK4Body> bodies = createBodies<RK4Body>(initPos,initVel,mass);
    for (int i = 1;i<iterations;++i)
    {
        auto itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK1(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK2(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK3(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeK4(bodies);
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
    savePositionsToFile<RK4Body>(bodies,"RK4Method");
}

void runLeapfrog(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{
    vector<LeapfrogBody> bodies = createBodies<LeapfrogBody>(initPos,initVel,mass);
    for (int i = 1;i<iterations;++i)
    {
        auto itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeCurrentAcceleration(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeNextAcceleration(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->applyChanges();
            ++itBodies;
        }
    }

    savePositionsToFile<LeapfrogBody>(bodies,"LeapfrogMethod");
}

void runVerlet(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{
    vector<VerletBody> bodies = createBodies<VerletBody>(initPos,initVel,mass);

    auto itBodies = bodies.begin();
    while(itBodies != bodies.end())
    {
        itBodies->computeFirstStep(bodies);
        ++itBodies;
    }

    itBodies = bodies.begin();
    while(itBodies != bodies.end())
    {
        itBodies->applyChanges();
        ++itBodies;
    }

    for (int i = 1;i<=iterations;++i)
    {
        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->computeNextStep(bodies);
            ++itBodies;
        }

        itBodies = bodies.begin();
        while(itBodies != bodies.end())
        {
            itBodies->applyChanges();
            ++itBodies;
        }
    }

    savePositionsToFile<VerletBody>(bodies,"VerletMethod");
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
    runEuler(initPositions,initVel,mass);
    runRK4(initPositions,initVel,mass);
    runLeapfrog(initPositions,initVel,mass);
    runVerlet(initPositions,initVel,mass);

    return 1;
}