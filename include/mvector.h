//
// Created by marco on 05.12.17.
//

#ifndef NBODYSOLVER_MVECTOR_H
#define NBODYSOLVER_MVECTOR_H

#include <vector>

using namespace std;

class MVector
{
private:
    typedef vector<double> vectorObj;
    vectorObj m_vector;
public:
    MVector()=default;
    MVector(const MVector &vec) {m_vector = vec.m_vector;};
    explicit MVector(const double &scalar){m_vector.push_back(scalar);}
    explicit MVector(vector<double> &vec){m_vector = vec;};

    ~MVector()= default;

    double operator [](int i) const {return m_vector[i];};
    double & operator [](int i){return m_vector[i];};

    void append(double scalar){m_vector.push_back(scalar);};
    void append(MVector vec){copy(vec.begin(),vec.end(),back_inserter(m_vector));};

    double abs();

    typedef vectorObj::iterator iterator;
    typedef vectorObj::const_iterator const_iterator;

    iterator begin() {return m_vector.begin();}
    iterator end() {return m_vector.end();}

    const unsigned long size(){return m_vector.size();}
    bool empty(){return m_vector.empty();}

    void zeros(int count){m_vector = vector<double>(count);};


    MVector& operator=(const MVector &vec);

    friend bool operator==(const MVector &vec1,const MVector &vec2);
    friend MVector operator+(const MVector &vec,const double &val);
    friend MVector operator+(MVector vec1,MVector vec2);
    friend MVector operator-(const MVector &vec,const double &val);
    friend MVector operator-(MVector vec1,MVector vec2);
    friend MVector operator*(const MVector &vec,const double &val);
    friend MVector operator*(const double &val,const MVector &vec);
    friend MVector operator*( MVector vec1, MVector vec2);
    friend MVector operator/(const MVector &vec, const double &val);

    friend MVector operator+=(const MVector &vec,const double &val);
    friend MVector operator+=(MVector vec1,MVector vec2);
    friend MVector operator-=(const MVector &vec,const double &val);
    friend MVector operator-=(MVector vec1,MVector vec2);
    friend MVector operator*=(const MVector &vec,const double &val);
    friend MVector operator*=(const double &val,const MVector &vec);
    friend MVector operator*=( MVector vec1, MVector vec2);
    friend MVector operator/=(const MVector &vec, const double &val);



};

#endif //NBODYSOLVER_MVECTOR_H
