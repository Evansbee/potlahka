#pragma once

#include "hittable.hpp"

class sphere : public hittable
{
public:
	sphere() {}
	sphere(const vec3 &c, real r) : center(c), radius(r) {}
	virtual bool hit(const ray& r, real tmin, real tmax, hit_record& record) const override;
	real radius;
	vec3 center;
};

bool sphere::hit(const ray& r, real tmin, real tmax, hit_record& record) const
{
	vec3 oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = dot(oc, r.direction);
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		real temp = (-b - sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(record.t);
			record.n = (record.p - center) / radius;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(record.t);
			record.n = (record.p - center) / radius;
			return true;
		}

	}
	return false;
}