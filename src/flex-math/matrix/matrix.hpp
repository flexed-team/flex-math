#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <iomanip> // std::setw
#include <xmmintrin.h>
#include <functional>

#include "matrix3.hpp"
#include "matrix4.hpp"
#include "square_matrix.hpp"

namespace FE
{

	class MatrixException : public std::runtime_error
	{
	public:
		MatrixException(std::string msg = "Unexepcted error") : runtime_error(msg.c_str()) {}
	};

	template <class T>
	class Matrix
	{
	protected:
		struct
		{
			uint8_t width, height;
		};

		/** Changes flow of accessing `v` array members */
		bool transposed;

		/** Matrix values array */
		T *values = nullptr;

		/**
		* Checks other matrix for size identity
		* Uses assert
		*/
		void check_sizes(Matrix<T> &m) const
		{
			assert(get_width() == m.get_width() && get_height() == m.get_height());
		}

		void increment_width() { transposed ? height++ : width++; }
		void increment_height() { transposed ? width++ : height++; }

	public:
		~Matrix() { delete[] values; }
		Matrix() : values{}, transposed(false) {}
		/** Copy constructor */
		Matrix(const Matrix<T> &matrix) : width(matrix.width), height(matrix.height), transposed(matrix.transposed)
		{
			values = new T[matrix.get_length()];
			std::copy(matrix.values, matrix.values + matrix.get_length(), values);
		}
		/** Skeleton constructor from array pointer */
		Matrix(const Matrix<T> &matrix, T array[]) : width(matrix.width), height(matrix.height), transposed(matrix.transposed)
		{
			values = new T[matrix.get_length()];
			std::copy(array, array + matrix.get_length(), values);
		}
		/** Skeleton constructor from vector */
		Matrix(const Matrix<T> &matrix, const std::vector<T> &vector) : width(matrix.width), height(matrix.height), transposed(matrix.transposed)
		{
			values = new T[matrix.get_length()];
			std::copy(vector.begin(), vector.end(), v);
		}
		/** Skeleton constructor from vector pointer */
		Matrix(const Matrix<T> &matrix, std::vector<T> *vector) : width(matrix.width), height(matrix.height), transposed(matrix.transposed)
		{
			values = new T[matrix.get_length()];
			std::copy(vector->begin(), vector->end(), values);
		}
		/** Size constructor */
		Matrix(uint8_t width, uint8_t height, bool transposed = false) : width(width), height(height), transposed(transposed)
		{
			values = new T[width * height];
		}
		/** Default value constructor(zero) */
		Matrix(uint8_t width, uint8_t height, T default_value, bool transposed = false) : width(width), height(height), transposed(transposed)
		{
			values = new T[width * height];
			std::fill(values, values + width * height, default_value);
		}
		/** From array pointer */
		Matrix(uint8_t width, uint8_t height, T array[], bool transposed = false) : width(width), height(height), transposed(transposed)
		{
			values = new T[width * height];
			std::copy(array, array + width * height, array);
		}
		/** From vector */
		Matrix(uint8_t width, uint8_t height, const std::vector<T> &vector, bool transposed = false) : width(width), height(height), transposed(transposed)
		{
			values = new T[width * height];
			std::copy(vector.begin(), vector.end(), vector);
		}
		/** From vector pointer */
		Matrix(uint8_t width, uint8_t height, std::vector<T> *vector, bool transposed = false) : width(width), height(height), transposed(transposed)
		{
			values = new T[width * height];
			std::copy(values->begin(), values->end(), vector);
		}

		// Getters
		/** Gets matrix values array size */
		uint8_t get_length() const { return width * height; }
		/** Gets matrix width */
		uint8_t get_width() const { return transposed ? height : width; }
		/** Gets matrix height */
		uint8_t get_height() const { return transposed ? width : height; }
		/** Gets matrix array */
		T *get_values() const { return v; }
		/** Gets `transposed` flag */
		bool get_transposed() const { return transposed; }

		/** Switches `transposed` flag to an opposite */
		void transpose() { transposed = !transposed; }

		/** Inserts row to matrix */
		void insert_row(T *row_values, uint8_t row_width)
		{
			assert(get_width() == row_width && "Inappropriate row size");
			const uint8_t offset = get_length();
			T *_values = new T[offset + row_width];
			std::copy(values, values + offset, _values);
			delete[] values;
			values = _values;
			for (uint8_t i = 0; i < row_width; i++)
				v[offset + i] = row_values[i];
			increment_height();
		}
		/** Inserts col to matrix */
		void insert_col(T *col_values, uint8_t col_height)
		{
			assert(g_h() == col_height && "Inappropriate col size");
			increment_width();
			const uint8_t new_length = get_length() + col_height;
			T *new_values = new t[new_length];
			uint8_t c = 0;
			for (uint8_t i = 0; i < new_length; i++)
			{
				if (i % get_width() == get_width() - 1)
				{
					_values[i] = col_values[c];
					c++;
				}
				else
					_values[i] = values[i - c];
			}
			delete[] values;
			values = _values;
		}

		/** Applies function for every element of matrix array */
		void for_each(std::function<void(T &)> callback)
		{
			for (uint8_t i = 0; i < g_length(); i++)
				callback(v[i]);
		}

		/**
		* Outputs matrix
		* Respects `transpose`
		*/
		void log()
		{
			for (uint8_t i = 0; i < get_height(); i++)
			{
				for (uint8_t j = 0; j < get_width(); j++)
				{
					std::cout << std::setw(5) << (*this)(i, j) << " ";
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		/** Identity matrix creation function */
		static Matrix<T> identity(uint8_t dimensions)
		{
			Matrix<T> M(dimensions, dimensions);
			for (uint8_t i = 0; i < dimensions; ++i)
			{
				for (uint8_t j = 0; j < dimensions; ++j)
					M(i, j) = (i == j ? 1.f : 0.f);
			}

			return M;
		}

		/** Converts Matrix to Vector3f */
		Vector3f to_vector3f()
		{
			assert(get_width() == 1 && get_height() == 4);
			return Vector3f((*this)(0, 0) / (*this)(0, 3), (*this)(0, 1) / (*this)(0, 3), (*this)(0, 2) / (*this)(0, 3));
		}

		// =
		Matrix<T> &operator=(const Matrix<T> &o)
		{
			width = o.width;
			height = o.height;
			transposed = o.transposed;

			delete[] values;
			values = new T[o.get_length()];
			std::copy(o.values, o.values + o.get_length(), values);

			return *this;
		}

		// +
		Matrix<T> operator+(float o)
		{
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] += o;
			return Matrix<t>((*this), _values);
		}
		Matrix<T> operator+(Matrix<T> &o)
		{
			check_sizes(o);
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] += o.v[i];
			return Matrix<t>((*this), _values);
		}

		// -
		/** Unary minus */
		Matrix<T> operator-()
		{
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] = -_values[i];
			return Matrix<t>((*this), _values);
		}
		Matrix<T> operator-(float o)
		{
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] -= o;
			return Matrix<t>((*this), _values);
		}
		Matrix<T> operator-(Matrix<T> &o)
		{
			check_sizes(o);
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] -= o.values[i];
			return Matrix<t>((*this), _values);
		}

		// *
		Matrix<T> operator*(float o)
		{
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] *= o;
			return Matrix<t>((*this), _values);
		}
		/** Perfmorms matrix multiplication */
		Matrix<T> operator*(Matrix<T> &o)
		{
			assert(get_width() == o.get_height() && "Multiply is impossible - origin matrix width is not equal other height");
			Matrix<t> matrix = Matrix<t>(o.get_width(), get_height(), t());
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t j = 0; j < o.get_width(); j++)
					for (uint8_t k = 0; k < get_width(); k++)
						matrix(i, j) += (*this)(i, k) * o(k, j);

			return matrix;
		}
		/** Perfmorms multiplication of matrix on 2d vector
		*	Matrix has to be width 2 and height at least 2 (all after 2nd row will be ignored)
		*/
		Vector2f operator*(const Vector2f &o)
		{
			assert(get_width() == 2 && get_height() >= 2 && "Inappropriate matrix dimensions for vector multiplication - width must be 2 and heigth at least 2");
			Vector2f vector = Vector2f();
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t k = 0; k < 2; k++)
					vector.raw[i] += (*this)(i, k) * o.raw[k];

			return vector;
		}
		/** Perfmorms multiplication of matrix on 3d vector
		*	Matrix has to be width 3 and height at least 3 (all after 3nd row will be ignored)
		*/
		Vector3f operator*(const Vector3f &o)
		{
			assert(get_width() == 3 && get_height() >= 3 && "Inappropriate matrix dimensions for vector multiplication - width must be 3 and heigth at least 3");
			Vector3f vector = Vector3f();
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t k = 0; k < 3; k++)
				{
					vector.raw[i] += (*this)(i, k) * o.raw[k];
				}

			return vector;
		}
		// /
		Matrix<T> operator/(float o)
		{
			T *_values = new T[get_length()];
			std::copy(values, values + get_length(), _values);
			for (uint8_t i = 0; i < get_length(); i++)
				_values[i] /= o;
			return Matrix<t>((*this), _values);
		}

		// ==
		bool operator==(float o)
		{
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t j = 0; j < get_width(); j++)
					if ((*this)(i, j) != o)
						return false;
			return true;
		}
		bool operator==(Matrix<T> &o)
		{
			check_sizes(o);
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t j = 0; j < get_width(); j++)
					if ((*this)(i, j) != o(i, j))
						return false;
			return true;
		}

		// !=
		bool operator!=(float o)
		{
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t j = 0; j < get_width(); j++)
					if ((*this)(i, j) == o)
						return false;
			return true;
		}
		bool operator!=(Matrix<T> &o)
		{
			check_sizes(o);
			for (uint8_t i = 0; i < get_height(); i++)
				for (uint8_t j = 0; j < get_width(); j++)
					if ((*this)(i, j) == o(i, j))
						return false;
			return true;
		}

		// +=
		Matrix<T> &operator+=(float o)
		{
			*this = *this + o;
			return *this;
		}
		Matrix<T> &operator+=(Matrix<T> &o)
		{
			*this = *this + o;
			return *this;
		}
		// -=
		Matrix<T> &operator-=(float o)
		{
			*this = *this - o;
			return *this;
		}
		Matrix<T> &operator-=(Matrix<T> &o)
		{
			*this = *this - o;
			return *this;
		}
		// *=
		Matrix<T> &operator*=(float o)
		{
			*this = *this * o;
			return *this;
		}
		Matrix<T> &operator*=(Matrix<T> &o)
		{
			*this = *this * o;
			return *this;
		}
		// /=
		Matrix<T> &operator/=(float o)
		{
			*this = *this / o;
			return *this;
		}
		// ++
		// Prefix increment operator
		Matrix<T> &operator++()
		{
			*this += 1;
			return *this;
		}
		// Postfix increment operator
		Matrix<T> operator++(int)
		{
			Matrix<t> temp = *this;
			++*this; // copied it from here https://docs.microsoft.com/ru-ru/cpp/cpp/increment-and-decrement-operator-overloading-cpp?view=vs-2019
			return temp;
		}
		// --
		// Prefix increment operator
		Matrix<T> &operator--()
		{
			*this -= 1;
			return *this;
		}
		// Postfix increment operator
		Matrix<T> operator--(int)
		{
			Matrix<t> temp = *this;
			--*this;
			return temp;
		}

		// Get elements operators

		/**
		* Implementation of 2d array [] operator.
		* Returns row by index
		*/
		std::vector<T> operator[](uint8_t i) const
		{
			// TODO: maybe return iterator?
			// FIXME: MAKE THIS
			//return std::vector<t>(v.begin() + i * get_width(), v.begin() + (i + 1) * get_width());
			return std::vector<T>(0);
		}

		/**
		* Implementation of 1d array [] operator
		* DON'T MIX UP WITH [] OPERATOR, THAT GETS MATRIX ROW
		* This one returns the actual element from values array
		*/
		T &operator()(uint8_t i)
		{
			return v[i];
		}

		/**
		* Implementation of 2d array [][] operator.
		* Returns matrix element
		*/
		T &operator()(uint8_t i1, uint8_t i2)
		{
			if (transposed)
				return v[c * width + r];
			return v[r * width + c];
		}

		/// <<
		template <class>
		friend std::ostream &operator<<(std::ostream &s, Matrix<T> &m);
	};

	template <class T>
	std::ostream &operator<<(std::ostream &s, Matrix<T> &m)
	{
		m.log();
		return s;
	}

	template <class T>
	std::ostream &operator<<(std::ostream &s, const Matrix<T> &m);

} // namespace FE