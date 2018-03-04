#pragma once

#include "config.hpp"
#include <iostream>
#include <cmath>
#include <xmmintrin.h>
#include <smmintrin.h>
class vec3
{
public:
	vec3() : vec3(real(), real(), real()) {}
	vec3(real a, real b, real c) : x(a), y(b), z(c), w(0.0f) {}
	vec3(__m128 in) : wide(in) {}
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
		return sqrtf(length_squared());
		__m128 wide;
		wide.m128_f32[0] = length_squared();
		return _mm_sqrt_ss(wide).m128_f32[0];
	}

	inline real length_squared() const
	{
		return d[0] * d[0] + d[1] * d[1] + d[2] * d[2];
	}

	inline void gamma_correct()
	{
		wide = _mm_sqrt_ps(wide);
	}

	inline void make_unit();

public:
	union
	{
		real d[4];
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
			union
			{
				real w;
				real a;
			};
		};
		__m128 wide;
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
	//__m128;

	//real k = real(1.0) / length();
	//__m128 widek = _mm_load_ps1(&k);
	//_mm_mul_ps(wide, widek);

	__m128 dot0 = _mm_dp_ps(wide, wide, 0xff);
	__m128 isr0 = _mm_rsqrt_ps(dot0);
	wide = _mm_mul_ps(wide, isr0);
}


inline vec3 operator +(const vec3 &v1, const vec3 &v2)
{
	return vec3(_mm_add_ps(v1.wide, v2.wide));
}


inline vec3 operator -(const vec3 &v1, const vec3 &v2)
{
	return vec3(_mm_sub_ps(v1.wide, v2.wide));
}

inline vec3 operator *(const vec3 &v1, const vec3 &v2)
{
	return vec3(_mm_mul_ps(v1.wide, v2.wide));
}

inline vec3 operator *(const vec3 &v1, real k)
{
	return vec3(_mm_mul_ps(v1.wide, _mm_load_ps1(&k)));
}

inline vec3 operator *(real k, const vec3 &v1)
{
	return v1 * k;

}


inline vec3 operator /(const vec3 &v1, real k)
{
	return vec3(_mm_div_ps(v1.wide, _mm_load_ps1(&k)));
}


inline real dot(const vec3 &v1, const vec3 &v2)
{
	__m128 res = _mm_dp_ps(v1.wide, v2.wide, 0xff);
	float test = v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];

	return res.m128_f32[0];
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}


inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
	__m128 swp0 = _mm_shuffle_ps(v1.wide, v1.wide, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 swp1 = _mm_shuffle_ps(v1.wide, v1.wide, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 swp2 = _mm_shuffle_ps(v2.wide, v2.wide, _MM_SHUFFLE(3, 0, 2, 1));
	__m128 swp3 = _mm_shuffle_ps(v2.wide, v2.wide, _MM_SHUFFLE(3, 1, 0, 2));
	__m128 mul0 = _mm_mul_ps(swp0, swp3);
	__m128 mul1 = _mm_mul_ps(swp1, swp2);
	return vec3(_mm_sub_ps(mul0, mul1));


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