#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
{
public:
    Vector();
    Vector(float x, float y, float z, float w = 1.0f);

public:
    static Vector add(Vector const& lhs, Vector const& rhs);
    static Vector sub(Vector const& lhs, Vector const& rhs);

    inline friend std::ostream& operator << (std::ostream& out, Vector const& vec)
    {
        out << '(' << vec.x_ << ',';
        out << vec.y_ << ',';
        out << vec.z_ << ',';
        out << vec.w_ << ')';

        return out;
    }

public:
    float x_;
    float y_;
    float z_;
    float w_;
};

#endif // VECTOR_H
