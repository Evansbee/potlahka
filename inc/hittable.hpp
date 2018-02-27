#pragma once

#include "config.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "material.hpp"

struct hit_record
{
	real t;
	vec3 p;
	vec3 n;
};

class hittable
{
public:
	virtual bool hit(const ray& r, real tmin, real tmax, hit_record &record) const = 0;
};