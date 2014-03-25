#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

/**
 * @brief Matrix class providing an interface for a 4x4 matrix. This matrix class provides an interface
 * for matrix operations and transformations.
 */
class Matrix
{
public:
    enum {
        ELEMS = 16,
        ROWS = 4,
        COLS = 4
    };

    // Index names to make accessing elements easier. Elements are ordered row first in memory.
    enum {
        M11 = 0, M12 = 1, M13 = 2, M14 = 3,
        M21 = 4, M22 = 5, M23 = 6, M24 = 7,
        M31 = 8, M32 = 9, M33= 10, M34= 11,
        M41= 12, M42= 13, M43= 14, M44= 15
    };

public:
    Matrix();

    Matrix& operator = (Matrix const& rhs);

    static Matrix identity();
    static Matrix scale3d(float x, float y, float z);

    /**
     * @brief multiplyColumnVector Performs a multiplication between a matrix and a column vector.
     * @param lhs The Matrix to multiply.
     * @param rhs The column Vector to multiply.
     * @return A Vector containing the result of the multiplication.
     */
    static Vector multiplyColumnVector(Matrix const& lhs, Vector const& rhs);

public:
    float m_[ELEMS];
};

#endif // MATRIX_H
