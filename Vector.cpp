#include "Vector.h"

#include <cmath>

Vector::Vector()
    : x_(0.0f), y_(0.0f), z_(0.0f), w_(1.0f)
{
}

Vector::Vector(float x, float y, float z, float w)
    : x_(x), y_(y), z_(z), w_(w)
{
}

Vector::Vector(Vector const& rhs)
    : x_(rhs.x_),
      y_(rhs.y_),
      z_(rhs.z_),
      w_(rhs.w_)
{
}

Vector& Vector::operator = (Vector const& rhs)
{
    x_ = rhs.x_;
    y_ = rhs.y_;
    z_ = rhs.z_;
    w_ = rhs.w_;

    return *this;
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

float Vector::mag() const
{
    return std::sqrt(x_*x_ + y_*y_ + z_*z_ + w_*w_);
}

float Vector::dotProduct(const Vector &lhs, const Vector &rhs)
{
    return lhs.x_*rhs.x_ +
           lhs.y_*rhs.y_ +
           lhs.z_*rhs.z_ +
           lhs.w_*rhs.w_;
}

Vector Vector::crossProduct(const Vector &lhs, const Vector &rhs)
{
    return Vector(
                lhs.y_*rhs.z_ - lhs.z_*rhs.y_,
                lhs.z_*rhs.x_ - lhs.x_*rhs.z_,
                lhs.x_*rhs.y_ - lhs.y_*rhs.x_
                );
}

Vector Vector::normalise(const Vector &v)
{
    float const m = v.mag();
    return Vector(
                v.x_ / m,
                v.y_ / m,
                v.z_ / m,
                v.w_ / m);
}

Vector Vector::operator + (Vector const& rhs) const
{
    return Vector::add(*this, rhs);
}

Vector Vector::operator - (Vector const& rhs) const
{
    return Vector::sub(*this, rhs);
}

Vector Vector::operator * (float rhs) const
{
    return Vector(
                x_ * rhs,
                y_ * rhs,
                z_ * rhs,
                w_ * rhs);
}

Vector Vector::operator / (float rhs) const
{
    return Vector(
                x_ / rhs,
                y_ / rhs,
                z_ / rhs,
                w_ / rhs);
}
