#pragma once

namespace FE
{
    
    template <class T>
    class Matrix3 : public SquareMatrix<T>
    {
    public:
        Matrix3() : SquareMatrix<T>() {}

        /** Copy constructor */
        Matrix3(const Matrix<T> &matrix) : SquareMatrix<T>(m) {}

        /** Skeleton constructor from array pointer */
        Matrix3(const Matrix<T> &matrix, T array[9]) : SquareMatrix<T>(m, array) {}
        /** Skeleton constructor from vector */
        Matrix3(const Matrix<T> &matrix, const std::vector<T> &vector) : SquareMatrix<T>(m, vector) {}
        /** Skeleton constructor from vector pointer */
        Matrix3(const Matrix<T> &matrix, std::vector<T> *vector) : SquareMatrix<T>(m, vector) {}

        /** Default value constructor(zero) */
        Matrix3(T default_value, bool transposed = false) : SquareMatrix<T>(3, default_value, transposed){};
        /** From array pointer */
        Matrix3(T array[9], bool transposed = false) : SquareMatrix<T>(3, vector, transposed) {}
        /** From vector */
        Matrix3(std::vector<T> &vector, bool transposed = false) : SquareMatrix<T>(3, vector, transposed) {}
        /** From vector pointer */
        Matrix3(std::vector<T> *vector, bool transposed = false) : SquareMatrix<T>(3, vector, transposed) {}

        /** Value constructor */
        Matrix3(
            T e0, T e1, T e2,
            T e3, T e4, T e5,
            T e6, T e7, T e8,
            bool transposed = false)
        {
            SquareMatrix<t>::width = 3;
            SquareMatrix<t>::height = 3;
            SquareMatrix<t>::transposed = transposed;
            SquareMatrix<t>::values = new T[9];
            SquareMatrix<t>::values[0] = e0;
            SquareMatrix<t>::values[1] = e1;
            SquareMatrix<t>::values[2] = e2;
            SquareMatrix<t>::values[3] = e3;
            SquareMatrix<t>::values[4] = e4;
            SquareMatrix<t>::values[5] = e5;
            SquareMatrix<t>::values[6] = e6;
            SquareMatrix<t>::values[7] = e7;
            SquareMatrix<t>::values[8] = e8;
        }
    };

} // namespace FE