#pragma once

namespace FE {
	template<class t> struct FE_API Vec2;
	template<class t> struct FE_API Vec3;

	typedef FE_API Vec2<float> Vec2f;
	typedef FE_API Vec2<int>   Vec2i;
	typedef FE_API Vec3<float> Vec3f;
	typedef FE_API Vec3<int>   Vec3i;

	class FE_API MatrixException;
	template<class t> class FE_API Matrix;
	template<class t> class FE_API SquareMatrix;
	template<class t> class FE_API Matrix3;
	template<class t> class FE_API Matrix4;

	typedef FE_API Matrix<int> Mati;
	typedef FE_API Matrix<float> Matf;
}