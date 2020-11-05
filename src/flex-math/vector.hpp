#pragma once

namespace FE
{

	template <class T>
	struct Vector2
	{
		union
		{
			struct
			{
				T x, y;
			};
			T raw[2];
		};
		Vector2() : u(T), v(T) {}
		Vector2(T u, T v) : u(u), v(v) {}
		Vector2<T> operator+(const Vector2<T> &o) const { return Vector2<t>(u + o.u, v + o.v); }
		Vector2<T> operator-(const Vector2<T> &o) const { return Vector2<t>(u - o.u, v - o.v); }
		Vector2<T> operator*(float o) const { return Vector2<t>(u * o, v * o); }

		Matrix<T> toMatrix()
		{
			Matrix<T> matrix(1, 3);
			matrix(0, 0) = x;
			matrix(0, 1) = y;
			matrix(0, 2) = (T)1;
			return matrix;
		};

		template <class T>
		friend std::ostream &operator<<(std::ostream &s, Vector2<T> &v);
	};

	template <class T>
	struct Vector3
	{
		union
		{
			struct
			{
				T x, y, z;
			};
			struct
			{
				T ivert, iuv, inorm;
			};
			T raw[3];
		};
		Vector3() : x(0), y(0), z(0) {}
		Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
		Vector3<T> operator^(const Vector3<T> &v) const { return Vector3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x); }
		Vector3<T> operator+(const Vector3<T> &v) const { return Vector3<T>(x + v.x, y + v.y, z + v.z); }
		Vector3<T> operator-(const Vector3<T> &v) const { return Vector3<T>(x - v.x, y - v.y, z - v.z); }
		Vector3<T> operator*(float f) const { return Vector3<T>(x * f, y * f, z * f); }
		T operator*(const Vector3<T> &v) const { return x * v.x + y * v.y + z * v.z; }
		float norm() const { return std::sqrt(x * x + y * y + z * z); }
		Vector3<T> &normalize(T l = 1)
		{
			*this = (*this) * (l / norm());
			return *this;
		}

		Matrix<T> toMatrix()
		{
			Matrix<T> M(1, 4);
			M(0, 0) = x;
			M(0, 1) = y;
			M(0, 2) = z;
			M(0, 3) = (T)1;
			return M;
		};

		template <class>
		friend std::ostream &operator<<(std::ostream &s, Vector3<T> &v);
	};

	template <class t>
	std::ostream &operator<<(std::ostream &s, Vector2<t> &v)
	{
		s << "(" << v.x << ", " << v.y << ")\n";
		return s;
	}

	template <class t>
	std::ostream &operator<<(std::ostream &s, Vector3<t> &v)
	{
		s << "(" << v.x << ", " << v.y << ", " << v.z << ")\n";
		return s;
	}
} // namespace FE