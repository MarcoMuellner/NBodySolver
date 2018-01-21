#include <fstream>
#include <math.h>
#include <iostream>

#include "eulerbody.h"
#include "rk4body.h"
#include "leapfrogbody.h"
#include "verletbody.h"
#include "helper.h"

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

template<class T>
void savePotentialEnergiesToFile(vector<T> bodies,string fileName)
{
    for(auto it = bodies.begin(); it!= bodies.end();++it)
    {
        ofstream out(fileName+"_E_POT_"+to_string(it->getID())+".txt");
        vector<double> values = it->getPotentialEnergyList();
        for(auto valueIt = values.begin();valueIt != values.end();++valueIt)
        {
            out<< (*valueIt) << "\n";
        }
    }
}

template<class T>
void saveKineticEnergiesToFile(vector<T> bodies,string fileName)
{
    for(auto it = bodies.begin(); it!= bodies.end();++it)
    {
        ofstream out(fileName+"_E_KIN_"+to_string(it->getID())+".txt");
        vector<double> values = it->getKineticEnergyHistory();
        for(auto valueIt = values.begin();valueIt != values.end();++valueIt)
        {
            out<< (*valueIt) << "\n";
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
    savePotentialEnergiesToFile<EulerBody>(bodies,"EulerMethod");
    saveKineticEnergiesToFile<EulerBody>(bodies,"EulerMethod");
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
    savePotentialEnergiesToFile<RK4Body>(bodies,"RK4Method");
    saveKineticEnergiesToFile<RK4Body>(bodies,"RK4Method");
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
    savePotentialEnergiesToFile<LeapfrogBody>(bodies,"LeapfrogMethod");
    saveKineticEnergiesToFile<LeapfrogBody>(bodies,"LeapfrogMethod");
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
    savePotentialEnergiesToFile<VerletBody>(bodies,"VerletMethod");
    saveKineticEnergiesToFile<VerletBody>(bodies,"VerletMethod");
}

void runAnalytical(vector<vector<double> > initPos, vector<vector<double> > initVel, vector<double > mass,int iterations = 1000)
{

}

void runAlgorithms(vector<vector<double> > initPositions, vector<vector<double> > initVelocities,vector<double> mass,int it = 1000)
{
    Timer t;
    /*
    runEuler(initPositions,initVelocities,mass,it);
    cout << "Euler finished, time is " << t.elapsed() << " seconds" << endl;
    t.reset();

    runRK4(initPositions,initVelocities,mass,it);
    cout << "RK4 finished, time is " << t.elapsed() << " seconds" << endl;
    t.reset();

    runLeapfrog(initPositions,initVelocities,mass,it);
     */
    runVerlet(initPositions,initVelocities,mass,it);
    cout <<"Leapfrog finished, time is " << t.elapsed() << " seconds" << endl;
}

void runNBodies(int bodies)
{
    vector<vector<double> > initPositions;
    vector<vector<double> > initVel;
    vector<double> mass;
    for(int i = 0;i<bodies;++i)
    {
        double x = rand()%bodies;
        double y = rand()%bodies;
        double v_x = rand()%bodies;
        double v_y = rand()%bodies;
        cout << i <<" Body position " << x << " " << y << endl;
        vector<double> pos = {x,y};
        vector<double> vel = {0,0};

        initPositions.push_back(pos);
        initVel.push_back(vel);
        mass.push_back(10);
    }
    runAlgorithms(initPositions,initVel,mass,5000);
}

int main(int argc, char *argv[])
{
    /*
    {
        vector<double> b1InitPos2D = {10,0};
        vector<double> b1InitVel2D = {0,0};

        vector<double> b2InitPos2D = {-10,0};
        vector<double> b2InitVel2D = {0,0};

        vector<double> mass = {10,10};
        vector<vector<double> > initPositions = {b1InitPos2D,b2InitPos2D};
        vector<vector<double> > initVel = {b1InitVel2D,b2InitVel2D};
        runAlgorithms(initPositions,initVel,mass,5000);
    }
     */


    /*
    {
        vector<double> b1InitPos2D = {5, 0};
        vector<double> b1InitVel2D = {0, sqrt(M_PI / 4.5)};

        vector<double> b2InitPos2D = {-5, 0};
        vector<double> b2InitVel2D = {0, -sqrt(M_PI / 4.5)};

        vector<double> b3InitPos2D = {0, 0};
        vector<double> b3InitVel2D = {0,-1};

        vector<double> mass = {10, 10, 10};
        vector<vector<double> > initPositions = {b1InitPos2D, b2InitPos2D, b3InitPos2D};
        vector<vector<double> > initVel = {b1InitVel2D, b2InitVel2D, b3InitVel2D};

        runAlgorithms(initPositions, initVel, mass);
    }
     */
    runNBodies(2);
    return 1;
}