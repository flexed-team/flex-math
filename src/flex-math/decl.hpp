#pragma once

namespace FE {
	template<class T> struct Vector2;
	template<class T> struct Vector3;

	class MatrixException;
	template<class T> class Matrix;
	template<class T> class SquareMatrix;
	template<class T> class Matrix3;
	template<class T> class Matrix4;

	typedef Vector2<float> Vector2f;
	typedef Vector3<float> Vector3f;
	typedef Matrix<float> Matf;
}