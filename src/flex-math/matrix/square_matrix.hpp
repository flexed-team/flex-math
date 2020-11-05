#pragma once

namespace FE
{
    
    template <class T>
    class SquareMatrix : public Matrix<T>
    {
    public:
        SquareMatrix() : Matrix<T>() {}

        /** Copy constructor */
        SquareMatrix(const Matrix<T> &matrix) : Matrix<T>(matrix) {}

        /** Skeleton constructor from array pointer */
        SquareMatrix(const Matrix<T> &matrix, T array[]) : Matrix<T>(matrix, array) {}
        /** Skeleton constructor from vector */
        SquareMatrix(const Matrix<T> &matrix, const std::vector<T> &vector) : Matrix<T>(matrix, vector) {}
        /** Skeleton constructor from vector pointer */
        SquareMatrix(const Matrix<T> &matrix, std::vector<T> *vector) : Matrix<T>(matrix, vector) {}

        /** Size constructor */
        SquareMatrix(uint8_t size, bool transposed = false) : Matrix<T>(size, size, transposed) {}
        /** Default value constructor(zero) */
        SquareMatrix(uint8_t size, T default_value, bool transposed = false) : Matrix<T>(size, size, default_value, transposed) {}
        /** From array pointer */
        SquareMatrix(uint8_t size, T array[], bool transposed = false) : Matrix<t>(size, size, array, transposed) {}
        /** From vector */
        SquareMatrix(uint8_t size, std::vector<T> &vector, bool transposed = false) : Matrix<t>(size, size, vector, transposed) {}
        /** From vector pointer */
        SquareMatrix(uint8_t size, std::vector<T> *vector, bool transposed = false) : Matrix<t>(size, size, vector, transposed) {}

        void insert_row() = delete;
        void insert_col() = delete;
        /** Returns the square matrix side size */
        uint8_t get_size() const { return Matrix<T>::width; }

        /** Gets a matrix of a lower order by cutting off row and column */
        SquareMatrix<T> lower_order(uint8_t row, uint8_t col)
        {
            std::vector<T> vector = std::vector<T>();
            for (uint8_t i = 0; i < get_size(); i++)
            {
                if (i == row)
                    continue;
                for (uint8_t j = 0; j < get_size(); j++)
                {
                    if (j == col)
                        continue;
                    vector.push_back((*this)(i, j));
                }
            }
            return SquareMatrix(get_size() - 1, vector, Matrix<t>::get_transposed());
        }

        /** Implementation of the Bareiss algorithm
		*	Copied from https://cs.nyu.edu/exact/core/download/core_v1.4/core_v1.4/progs/bareiss/bareiss.cpp
		*
		*   Note that this implementation can include divisions by zero which will return nan
		*
		*   To fix this you have to swap rows with 0 on iteration change,
		*   like here https://www.math.usm.edu/perry/Research/Thesis_DRL.pdf (type "Division by Zero in Bareiss" while on page to find solution)
		*	This is very expensive solution, but even it won't give acceptable results as after swap 0 can still be on its place
		*   so wee need to look up a whole col to find non-zero element, which is even more expensive
		*
		*	But as far as I know every algorithm that has complexity O(N^3) and lower encounters this problem
		*/
        long double determinant()
        {
            SquareMatrix<t> M = *this;
            const uint8_t size = M.get_size();

            bool change_sign = false;
            bool swapped = false;
            for (uint8_t i = 0; i < size - 1; i++)
            {
                if (i < get_size() - 2 && M(i, i) == 0)
                { // All inside this if condition is needed to fix zero-division
                    if (M(i + 1, i) != 0)
                    { // Swap with next row if the value under is non-zero
                        M.swap_rows(i, i + 1);
                        swapped = true;
                    }
                    else
                        for (uint8_t l = 0; l < A.height; l++)
                        { // Else try to find non-zero elemnt in column and swap with it
                            if (M(l, i) != 0)
                            {
                                M.swap_rows(i, l);
                                swapped = true;
                                break;
                            }
                        }

                    if (!swapped)
                        return 0;
                    swapped = false;

                    // By determinate property: when you swap column or row with another the sign of determinate will change to an opposite
                    change_sign = !change_sign;
                }

                for (uint8_t j = i + 1; j < size; j++)
                    for (uint8_t k = i + 1; k < size; k++)
                    {
                        M(j, k) = (M(j, k) * M(i, i) - M(j, i) * M(i, k));
                        if (i) // Don't divide on first iteration
                            M(j, k) /= M(i - 1, i - 1);
                    }
            }

            return change_sign ? -1 * A(size - 1, size - 1) : A(size - 1, size - 1);
        }

        void swap_rows(uint8_t r1, uint8_t r2)
        {
            for (uint8_t i = 0; i < Matrix<T>::get_width(); i++)
            {
                std::swap((*this)(r1, i), (*this)(r2, i));
            }
        }

        /** Finds minor of matrix */
        long double minor(uint8_t r, uint8_t c)
        {
            return cut_matrix(r, c).determinant();
        }

        /** Finds algebraic */
        long double complement(uint8_t r, uint8_t c)
        {
            return (((r + c) % 2) ? -1 : 1) * (minor)(r, c);
        }

        /** Returns inverse matrix */
        SquareMatrix<T> inverse()
        {
            long double det = determinant();
            if (det == 0)
                throw MatrixException("Can't inverse: determinant equals zero");

            // Find adjoint matrix
            SquareMatrix<T> M = *this;
            for (uint8_t i = 0; i < get_size(); i++)
            {
                for (uint8_t j = 0; j < get_size(); j++)
                {
                    M(i, j) = complement(i, j);
                }
            }
            M.transpose();
            M /= det;
            return M;
        }
    };

} // namespace FE