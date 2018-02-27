#pragma once

#include "config.hpp"
#include "vec3.hpp"

class ray
{
public:
	ray() {};
	ray(const vec3 &a, const vec3 &b) : origin(a), direction(b) {}
	vec3 point_at_parameter(real t) const { return origin + t * direction; }
	vec3 origin;
	vec3 direction;
};
