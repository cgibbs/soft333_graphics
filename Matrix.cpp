#include "Matrix.h"

#include <cstdint>

using std::size_t;

Matrix::Matrix()
{
    // Initialise all elements of the matrix to 0.
    for(size_t i = 0; i < ELEMS; i++) {
        m_[i] = 0.0f;
    }
}

Matrix& Matrix::operator = (Matrix const& rhs)
{
    // Copy the elements of the matrix.
    for(size_t i = 0; i < ELEMS; i++) {
        this->m_[i] = rhs.m_[i];
    }

    return *this;
}

Matrix Matrix::identity()
{
    Matrix mat;

    mat.m_[M11] = 1.0f;
    mat.m_[M22] = 1.0f;
    mat.m_[M33] = 1.0f;
    mat.m_[M44] = 1.0f;

    return mat;
}

Matrix Matrix::scale3d(float x, float y, float z)
{
    Matrix mat;
    mat.m_[M11] = x;
    mat.m_[M22] = y;
    mat.m_[M33] = z;
    mat.m_[M44] = 1.0f;

    return mat;
}

Vector Matrix::multiplyColumnVector(const Matrix &lhs, const Vector &rhs)
{
    Vector v;
    v.x_ = lhs.m_[M11]*rhs.x_ + lhs.m_[M12]*rhs.y_ + lhs.m_[M13]*rhs.z_ + lhs.m_[M14]*rhs.w_;
    v.y_ = lhs.m_[M21]*rhs.x_ + lhs.m_[M22]*rhs.y_ + lhs.m_[M23]*rhs.z_ + lhs.m_[M24]*rhs.w_;
    v.z_ = lhs.m_[M31]*rhs.x_ + lhs.m_[M32]*rhs.y_ + lhs.m_[M33]*rhs.z_ + lhs.m_[M34]*rhs.w_;
    v.w_ = lhs.m_[M41]*rhs.x_ + lhs.m_[M42]*rhs.y_ + lhs.m_[M43]*rhs.z_ + lhs.m_[M44]*rhs.w_;

    return v;
}
