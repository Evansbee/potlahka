#pragma once

#include "hittable.hpp"
#include "material.hpp"
#include <memory>
class sphere : public hittable
{
public:
	sphere() {}
	sphere(const vec3 &c, real r, material *matl) : m_Center(c), m_Radius(r), m_Material(matl) {}
	virtual bool hit(const ray& r, real tmin, real tmax, hit_record& record) const override;
private:
	real m_Radius;
	vec3 m_Center;
	material *m_Material;
};

bool sphere::hit(const ray& r, real tmin, real tmax, hit_record& record) const
{
	vec3 oc = r.origin - m_Center;
	real a = dot(r.direction, r.direction);
	real b = dot(oc, r.direction);
	real c = dot(oc, oc) - m_Radius * m_Radius;
	real discriminant = b * b - a * c;
	if (discriminant > 0)
	{
		real temp = (-b - sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(record.t);
			record.n = (record.p - m_Center) / m_Radius;
			record.mat = m_Material;
			return true;
		}
		temp = (-b + sqrt(discriminant)) / a;
		if (temp < tmax && temp > tmin)
		{
			record.t = temp;
			record.p = r.point_at_parameter(record.t);
			record.n = (record.p - m_Center) / m_Radius;
			record.mat = m_Material;
			return true;
		}

	}
	return false;
}