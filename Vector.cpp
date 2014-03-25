#include "Vector.h"

Vector::Vector()
    : x_(0.0f), y_(0.0f), z_(0.0f), w_(1.0f)
{
}

Vector::Vector(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w)
{
}

Vector Vector::add(const Vector &lhs, const Vector &rhs)
{
    return Vector(
                lhs.x_ + rhs.x_,
                lhs.y_ + rhs.y_,
                lhs.z_ + rhs.z_,
                lhs.w_ + rhs.w_
                );
}

Vector Vector::sub(const Vector &lhs, const Vector &rhs)
{
    return Vector(
                lhs.x_ - rhs.x_,
                lhs.y_ - rhs.y_,
                lhs.z_ - rhs.z_,
                lhs.w_ - rhs.w_
                );
}
