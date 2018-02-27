#pragma once


#include "vec3.hpp"

template <typename T>
class ray
{
public:
	ray() {};
	ray(const vec3<T> &a, const vec3<T> &b) : origin(a), direction(b) {}
	vec3<T> point_at_parameter(T t) const { return origin + t * direction; }
	vec3<T> origin;
	vec3<T> direction;
};

typedef ray<float> rayf;
typedef ray<double> rayd;