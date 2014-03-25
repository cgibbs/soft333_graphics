#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
public:
    Vector();
    Vector(float x, float y, float z, float w = 1.0f);

public:
    static Vector add(Vector const& lhs, Vector const& rhs);
    static Vector sub(Vector const& lhs, Vector const& rhs);

public:
    float x_;
    float y_;
    float z_;
    float w_;
};

#endif // VECTOR_H
