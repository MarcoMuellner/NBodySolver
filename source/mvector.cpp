//
// Created by marco on 05.12.17.
//

#include "mvector.h"
#include <math.h>

MVector& MVector::operator=(const MVector &vec)
{
    if(this == &vec)
        return *this;
    m_vector = vec.m_vector;
    return *this;
}

double MVector::abs()
{
    double val = 0;

    for(auto it = m_vector.begin();it!=m_vector.end();++it)
    {
        val += pow((*it),2);
    }

    return sqrt(val);
}

MVector operator+(const MVector &vec,const double &val)
{
    MVector retVec;
    for(auto it = vec.m_vector.begin();it !=vec.m_vector.end();++it)
    {
        retVec.append((*it)+val);
    }
    return retVec;
}

MVector operator-(const MVector &vec,const double &val)
{
    MVector retVec;
    for(auto it = vec.m_vector.begin();it !=vec.m_vector.end();++it)
    {
        retVec.append((*it)-val);
    }
    return retVec;
}

MVector operator*(const MVector &vec,const double &val)
{
    MVector retVec;
    for(auto it = vec.m_vector.begin();it !=vec.m_vector.end();++it)
    {
        retVec.append((*it)*val);
    }
    return retVec;
}

MVector operator*(const double &val,const MVector &vec)
{
    return vec*val;
}

MVector operator*(MVector vec1, MVector vec2)
{
    MVector retVec;
    if (vec1.size() == vec2.size())
    {
        auto itObj1 = vec1.begin();
        auto itObj2 = vec2.begin();

        while(itObj1 != vec1.end() && itObj2 != vec2.end())
        {
            retVec.append((*itObj1)*(*itObj2));
            ++itObj1;
            ++itObj2;
        }
    }
    return retVec;
}

MVector operator/(const MVector &vec,const double &val)
{
    MVector retVec;
    for(auto it = vec.m_vector.begin();it !=vec.m_vector.end();++it)
    {
        retVec.append((*it)/val);
    }
    return retVec;
}

MVector operator+(MVector vec1,MVector vec2)
{
    MVector retVec;
    if (vec1.size() == vec2.size())
    {
        auto itVec1 = vec1.begin();
        auto itVec2 = vec2.begin();

        while(itVec1 != vec1.end() && itVec2 != vec2.end())
        {
            retVec.append((*itVec1)+(*itVec2));

            ++itVec1;
            ++itVec2;
        }
    }
    return retVec;
}

MVector operator-(MVector vec1,MVector vec2)
{
    MVector retVec;
    if (vec1.size() == vec2.size())
    {
        auto itVec1 = vec1.begin();
        auto itVec2 = vec2.begin();

        while(itVec1 != vec1.end() && itVec2 != vec2.end())
        {
            retVec.append((*itVec1)-(*itVec2));

            ++itVec1;
            ++itVec2;
        }
    }
    return retVec;
}

MVector operator+=(const MVector &vec,const double &val)
{
    return vec + val;
}

MVector operator-=(const MVector &vec,const double &val)
{
    return vec - val;
}

MVector operator*=(const MVector &vec,const double &val)
{
    return vec*val;
}

MVector operator*=(const double &val,const MVector &vec)
{
    return vec*val;
}

MVector operator*=( MVector vec1, MVector vec2)
{
    return vec1*vec2;
}

MVector operator/=(const MVector &vec, const double &val)
{
    return vec/val;
}

MVector operator+=(MVector vec1,MVector vec2)
{
    return vec1 + vec2;
}

MVector operator-=(MVector vec1,MVector vec2)
{
    return vec1 - vec2;
}

bool operator==(const MVector &vec1,const MVector &vec2)
{
    return vec1.m_vector == vec2.m_vector;
}