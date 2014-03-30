#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector
{
public:
    Vector();
    Vector(Vector const& v);
    Vector(float x, float y, float z, float w = 1.0f);

    Vector& operator = (Vector const& rhs);

public:
    float mag() const;

public:
    static Vector add(Vector const& lhs, Vector const& rhs);
    static Vector sub(Vector const& lhs, Vector const& rhs);

    Vector operator + (Vector const& rhs) const;
    Vector operator - (Vector const& rhs) const;

    Vector operator * (float rhs) const;
    Vector operator / (float rhs) const;

    inline friend std::ostream& operator << (std::ostream& out, Vector const& vec)
    {
        out << '(' << vec.x_ << ',';
        out << vec.y_ << ',';
        out << vec.z_ << ',';
        out << vec.w_ << ')';

        return out;
    }

    static float dotProduct(Vector const& lhs, Vector const& rhs);

    static Vector crossProduct(Vector const& lhs, Vector const& rhs);

    static Vector normalise(Vector const& v);



public:
    float x_;
    float y_;
    float z_;
    float w_;
};

#endif // VECTOR_H
