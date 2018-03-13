//
// Created by marco on 05.12.17.
//

#ifndef NBODYSOLVER_MVECTOR_H
#define NBODYSOLVER_MVECTOR_H

#include <vector>
#include <string>

using namespace std;

class MVector
{
private:
    typedef vector<double> vectorObj;
    vectorObj m_vector;
public:
    /**
     * Constructor initializing the data with an empty vector object.
     */
    MVector(){m_vector = vectorObj();}
    /**
     * Copy constructor, copies the vec object from foreign instance to lokal instance
     * @param vec MVector object to be copied
     */
    MVector(const MVector &vec) {m_vector = vec.m_vector;};
    /**
     * Constructor initializing the data with a single datapoint. Explicit to prohibit internal shananigans of the
     * compiler
     * @param scalar first value in vector object
     */
    explicit MVector(const double &scalar){m_vector.push_back(scalar);}
    /**
     * Constructor initializing the data with a std::vector object. Probably most usecases would apply to this.
     * Explicit to prohibit internal shananigans of the compiler. Reference wise passing of parameter.
     * @param vec std::vector object containing the data. Sequence will stay the same
     */
    explicit MVector(vector<double> &vec){m_vector = vec;};
    /**
     * Constructor initializing the data with a std::vector object. Probably most usecases would apply to this.
     * Explicit to prohibit internal shananigans of the compiler. Full copy of parameter.
     * @param vec std::vector object containing the data. Sequence will stay the same
     */
    explicit MVector(const vector<double> &vec){m_vector = vec;};

    ~MVector()= default;

    /**
     * Access operator. Returns item at point i. Returns full value.
     * @param i Sequence item
     * @return double value of coordinate.
     */
    double operator [](int i) const {return m_vector[i];};
    /**
     * Access operator. Returns item at point i. Returns reference to item.
     * @param i Sequence item
     * @return double value of coordinate.
     */
    double & operator [](int i){return m_vector[i];};

    void append(double scalar){m_vector.push_back(scalar);};
    void append(MVector vec){copy(vec.begin(),vec.end(),back_inserter(m_vector));};

    /**
     * Absolute value of vector. Iterates over components of vector, squares it and takes the squareroot of the sum.
     * @return Scalar absolute value of vector.
     */
    double abs(double additionalFactor = 0.0);

    typedef vectorObj::iterator iterator;
    typedef vectorObj::const_iterator const_iterator;

    iterator begin() {return m_vector.begin();}
    iterator end() {return m_vector.end();}

    const unsigned long size(){return m_vector.size();}
    bool empty(){return m_vector.empty();}

    MVector &zeros(unsigned long count){m_vector = vector<double>(count);return *this;};

    string toString();

    /**
     * Assignment operator for MVector class. Assigns std::vector to current instance. Full copy of vector
     * @param vec Vector to assigned with
     * @return Instance of this class
     */
    MVector& operator=(const MVector &vec);


    friend bool operator==(const MVector &vec1,const MVector &vec2);
    /**
     * Plus operator for MVector class. Adds a scalar to every item of the vector
     * @note This could be improved using a lamda function (std::for_each or std::transform)
     * @param vec vector to be added with
     * @param val scalar value to be added
     * @return vector of size of vec
     */
    friend MVector operator+(const MVector &vec,const double &val);
    /**
     * Itemwhise addition of two vectors.
     */
    friend MVector operator+(MVector vec1,MVector vec2);
    /**
    * Minus operator for MVector class. Subtracts a scalar for every item of the vector
     * @param vec  vector to be subracted from
     * @param val  scalar value to be subtracted
     * @return vector of size of vec
     */
    friend MVector operator-(const MVector &vec,const double &val);
    /**
     * Itemwhise subtraction of two vectors
     */
    friend MVector operator-(MVector vec1,MVector vec2);
    /**
     * Multiplication of vector with scalar.
     * @param vec vector to be multiplied with
     * @param val scalar value to be multiplied with
     * @return vector of size vec
     */
    friend MVector operator*(const MVector &vec,const double &val);
    /**
     * Redundant class to allow scalar*vector
     * @see operator*
     */
    friend MVector operator*(const double &val,const MVector &vec);
    /**
     * Itemwhise multiplication of two vectors. Both vectors have to have equal size. Otherwhise will return empty vector
     * @return Vector of size vec1 and 2.
     */
    friend MVector operator*( MVector vec1, MVector vec2);
    /**
     * Divides all elements of the vector by val
     */
    friend MVector operator/(const MVector &vec, const double &val);
    friend double dot(const MVector &vec1,const MVector &vec2);

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
