#pragma once

#include "hittable.hpp"
#include "material.hpp"
class sphere : public hittable
{
public:
	sphere() {}
	sphere(const vec3 &c, real r, material *matl) : center(c), radius(r),mat(matl) {}
	virtual bool hit(const ray& r, real tmin, real tmax, hit_record& record) const override;
	real radius;
	vec3 center;
	material *mat;
};

bool sphere::hit(const ray& r, real tmin, real tmax, hit_record& record) const
{
	vec3 oc = r.origin - center;
	real a = dot(r.direction, r.direction);
	real b = dot(oc, r.direction);
	real c = dot(oc, oc) - radius * radius;
	real discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		real temp = (-b - sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(record.t);
			record.n = (record.p - center) / radius;
			record.mat = mat;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(record.t);
			record.n = (record.p - center) / radius;
			record.mat = mat;
			return true;
		}

	}
	return false;
}