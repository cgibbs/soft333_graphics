#include "Matrix.h"

#include <cstdint>
#include <cmath>

using std::size_t;

Matrix::Matrix()
{
    // Initialise all elements of the matrix to 0.
    for(size_t i = 0; i < ELEMS; i++) {
        m_[i] = 0.0f;
    }
}

Matrix::Matrix(const Matrix &m)
{
    // Intialise each element of the matrix.
    for(size_t i = 0; i < ELEMS; i++) {
        m_[i] = m.m_[i];
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

Matrix Matrix::translate3d(float x, float y, float z)
{
    Matrix mat = identity();

    mat.m_[M14] = x;
    mat.m_[M24] = y;
    mat.m_[M34] = z;

    return mat;
}

Matrix Matrix::rotateX(float rad)
{
    Matrix m = identity();
    m.m_[M22] = std::cos(rad);
    m.m_[M23] = std::sin(rad);
    m.m_[M32] = -std::sin(rad);
    m.m_[M33] = std::cos(rad);

    return m;
}

Matrix Matrix::rotateY(float rad)
{
    Matrix m = identity();
    m.m_[M11] = std::cos(rad);
    m.m_[M13] = -std::sin(rad);
    m.m_[M31] = std::sin(rad);
    m.m_[M33] = std::cos(rad);

    return m;
}

Matrix Matrix::rotateZ(float rad)
{
    Matrix m = identity();
    m.m_[M11] = std::cos(rad);
    m.m_[M12] = std::sin(rad);
    m.m_[M21] = -std::sin(rad);
    m.m_[M22] = std::cos(rad);

    return m;
}

Matrix Matrix::perspective(float focus)
{
    Matrix m = identity();

    return m;
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

Matrix Matrix::multiplyMatrix(const Matrix &lhs, const Matrix &rhs)
{
    Matrix m;

    for(size_t r = 0; r < Matrix::ROWS; r++)
    {
        for(size_t c = 0; c < Matrix::COLS; c++) {

            float dp =
                    lhs.m_[0 + r * COLS] * rhs.m_[c + 0 * COLS] +
                    lhs.m_[1 + r * COLS] * rhs.m_[c + 1 * COLS] +
                    lhs.m_[2 + r * COLS] * rhs.m_[c + 2 * COLS] +
                    lhs.m_[3 + r * COLS] * rhs.m_[c + 3 * COLS];

            m.m_[c + r * COLS] = dp;

        }
    }

    return m;
}
