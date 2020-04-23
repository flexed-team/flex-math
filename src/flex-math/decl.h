#pragma once

#include "core.h"

// TODO resturcture this file maybe
namespace FE {
	template<class t> struct Vec2;
	template<class t> struct Vec3;

	typedef Vec2<float> Vec2f;
	typedef Vec2<int>   Vec2i;
	typedef Vec3<float> Vec3f;
	typedef Vec3<int>   Vec3i;

	class MatrixException;
	template<class t> class Matrix;
	template<class t> class SquareMatrix;
	template<class t> class Matrix3;
	template<class t> class Matrix4;

	typedef Matrix<int> Mati;
	typedef Matrix<float> Matf;
}