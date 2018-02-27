#pragma once

#include <cmath>
#include <iostream>

template <typename T>
class vec3
{
public:
	vec3() : vec3(T(), T(), T()) {}
	vec3(T a, T b, T c) : x(a), y(b), z(c) {}

	inline const vec3<T>& operator+() const { return *this; }
	inline const vec3<T>& operator-() const { return vec3<T>(-x, -y, -z); }

	inline T operator[](int i) const { return d[i]; }
	inline T& operator[](int i) { return d[i]; }

	inline vec3<T>& operator += (const vec3<T> &other);
	inline vec3<T>& operator -= (const vec3<T> &other);
	inline vec3<T>& operator *= (const vec3<T> &other);
	inline vec3<T>& operator /= (const vec3<T> &other);
	inline vec3<T>& operator *= (T other);
	inline vec3<T>& operator /= (T other);

	inline T length() const
	{
		return sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
	}

	inline T length_squared() const
	{
		return d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
	}

	inline void make_unit();

public:
	union
	{
		T d[3];
		struct
		{
			union
			{
				T x;
				T r;
			};
			union
			{
				T y;
				T g;
			};
			union
			{
				T z;
				T b;
			};
		};
	};

};

typedef vec3<float> vec3f;
typedef vec3<double> vec3d;


template <typename T>
inline std::istream& operator >> (std::istream &is, vec3<T>& v)
{
	is >> t[0] >> t[1] >> t[2];
	return is;
}

template <typename T>
inline std::ostream& operator<<(std::ostream &os, const vec3<T>& v)
{
	os << v.x << " " << v.y << " " << v.z;
	return os;
}

template <typename T>
inline void vec3<T>::make_unit()
{
	T k = T(1.0) / length();
	d[0] *= k;
	d[1] *= k;
	d[2] *= k;
}

template <typename T>
inline vec3<T> operator +(const vec3<T> &v1, const vec3<T> &v2)
{
	return vec3<T>(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

template <typename T>
inline vec3<T> operator -(const vec3<T> &v1, const vec3<T> &v2)
{
	return vec3<T>(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

template <typename T>
inline vec3<T> operator *(const vec3<T> &v1, T k)
{
	return vec3<T>(v1[0] * k, v1[1] * k, v1[2] * k);
}

template <typename T>
inline vec3<T> operator *(T k, const vec3<T> &v1)
{
	return vec3<T>(v1[0] * k, v1[1] * k, v1[2] * k);
}

template <typename T>
inline vec3<T> operator /(const vec3<T> &v1, T k)
{
	return vec3<T>(v1[0] / k, v1[1] / k, v1[2] / k);
}

template <typename T>
inline T dot(const vec3<T> &v1, const vec3<T> &v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

template <typename T>
inline vec3<T> cross(const vec3<T> &v1, const vec3<T> &v2)
{
	return vec3<T>(v1[1] * v2[2] - v1[2] * v2[1],
		-(v1[0] * v2[2] - v1[2] * v2[0]),
		v1[0] * v2[1] - v1[1] * v2[0]);
}

template <typename T>
inline vec3<T> unit_vector(const vec3<T> &v)
{
	vec3<T> uv = v;
	uv.make_unit();
	return uv;
}