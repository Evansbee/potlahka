#pragma once

#include "config.hpp"
#include <cmath>
#include <iostream>

class vec3
{
public:
	vec3() : vec3(real(), real(), real()) {}
	vec3(real a, real b, real c) : x(a), y(b), z(c) {}

	inline const vec3& operator+() const { return *this; }
	inline const vec3 operator-() const { return vec3(-x, -y, -z); }

	inline real operator[](int i) const { return d[i]; }
	inline real& operator[](int i) { return d[i]; }

	inline vec3& operator += (const vec3 &other);
	inline vec3& operator -= (const vec3 &other);
	inline vec3& operator *= (real other);
	inline vec3& operator /= (real other);

	inline real length() const
	{
		return sqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
	}

	inline real length_squared() const
	{
		return d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
	}

	inline void make_unit();

public:
	union
	{
		real d[3];
		struct
		{
			union
			{
				real x;
				real r;
			};
			union
			{
				real y;
				real g;
			};
			union
			{
				real z;
				real b;
			};
		};
	};

};



inline std::istream& operator >> (std::istream &is, vec3& v)
{
	is >> v[0] >> v[1] >> v[2];
	return is;
}


inline std::ostream& operator<<(std::ostream &os, const vec3& v)
{
	os << v.x << " " << v.y << " " << v.z;
	return os;
}


inline void vec3::make_unit()
{
	real k = real(1.0) / length();
	d[0] *= k;
	d[1] *= k;
	d[2] *= k;
}


inline vec3 operator +(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}


inline vec3 operator -(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}

inline vec3 operator *(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1[0] * v2[0], v1[1] * v2[1], v1[2] * v2[2]);
}

inline vec3 operator *(const vec3 &v1, real k)
{
	return vec3(v1[0] * k, v1[1] * k, v1[2] * k);
}

inline vec3 operator *(real k, const vec3 &v1)
{
	return vec3(v1[0] * k, v1[1] * k, v1[2] * k);
}


inline vec3 operator /(const vec3 &v1, real k)
{
	return vec3(v1[0] / k, v1[1] / k, v1[2] / k);
}


inline real dot(const vec3 &v1, const vec3 &v2)
{
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
	return vec3(v1[1] * v2[2] - v1[2] * v2[1],
		-(v1[0] * v2[2] - v1[2] * v2[0]),
		v1[0] * v2[1] - v1[1] * v2[0]);
}

inline vec3 unit_vector(const vec3 &v)
{
	vec3 uv = v;
	uv.make_unit();
	return uv;
}


inline vec3& vec3::operator += (const vec3 &other) { *this = *this + other;  return *this; }
inline vec3& vec3::operator -= (const vec3 &other) { *this = *this - other;  return *this; }
inline vec3& vec3::operator *= (real other) { *this = *this * other;  return *this; }
inline vec3& vec3::operator /= (real other) { *this = *this / other;  return *this; }

inline vec3 reflect(const vec3& in, const vec3& n)
{
	return in - 2.0*dot(in, n)*n;
}