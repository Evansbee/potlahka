#pragma once

#include "config.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class material;


struct hit_record
{
	real t;
	vec3 p;
	vec3 n;
	material *mat;
};

class hittable
{
public:
	virtual bool hit(const ray& r, real tmin, real tmax, hit_record &record) const = 0;
};