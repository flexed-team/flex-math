#pragma once

namespace FE
{

    template <class T>
    class Matrix4 : public SquareMatrix<T>
    {
    public:
        Matrix4() : SquareMatrix<T>() {}

        /** Copy constructor */
        Matrix4(const Matrix<T> &matrix) : SquareMatrix<T>(matrix) {}

        /** Skeleton constructor from array pointer */
        Matrix4(const Matrix<T> &matrix, T array[16]) : SquareMatrix<T>(matrix, array) {}
        /** Skeleton constructor from vector */
        Matrix4(const Matrix<T> &matrix, const std::vector<T> &vector) : SquareMatrix<T>(matrix, vector) {}
        /** Skeleton constructor from vector pointer */
        Matrix4(const Matrix<T> &matrixm, std::vector<T> *vector) : SquareMatrix<T>(matrix, vector) {}

        /** Default value constructor(zero) */
        Matrix4(T default_value, bool transposed = false) : SquareMatrix<T>(4, default_value, transposed) {}
        /** From array pointer */
        Matrix4(T array[16], bool transposed = false) : SquareMatrix<T>(4, array, transposed) {}
        /** From vector */
        Matrix4(std::vector<T> &vector, bool transposed = false) : SquareMatrix<T>(4, vector, transposed) {}
        /** From vector pointer */
        Matrix4(std::vector<T> *vector, bool transposed = false) : SquareMatrix<T>(4, vector, transposed) {}
        /** Value constructor */
        Matrix4(
            T e0, T e1, T e2, T e3,
            T e4, T e5, T e6, T e7,
            T e8, T e9, T e10, T e11,
            T e12, T e13, T e14, T e15,
            bool transposed = false)
        {
            SquareMatrix<T>::width = 4;
            SquareMatrix<T>::height = 4;
            SquareMatrix<T>::transposed = transposed;
            SquareMatrix<T>::values = new T[16];
            SquareMatrix<T>::values[0] = e0;
            SquareMatrix<T>::values[1] = e1;
            SquareMatrix<T>::values[2] = e2;
            SquareMatrix<T>::values[3] = e3;
            SquareMatrix<T>::values[4] = e4;
            SquareMatrix<T>::values[5] = e5;
            SquareMatrix<T>::values[6] = e6;
            SquareMatrix<T>::values[7] = e7;
            SquareMatrix<T>::values[8] = e8;
            SquareMatrix<T>::values[9] = e9;
            SquareMatrix<T>::values[10] = e10;
            SquareMatrix<T>::values[11] = e11;
            SquareMatrix<T>::values[12] = e12;
            SquareMatrix<T>::values[13] = e13;
            SquareMatrix<T>::values[14] = e14;
            SquareMatrix<T>::values[15] = e15;
        }
    };

} // namespace FE