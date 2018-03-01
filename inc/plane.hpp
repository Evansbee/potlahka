#pragma once

#include <limits>

#include "config.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "hittable.hpp"
#include "material.hpp"
class plane : public hittable
{
   public:
      plane() {}
	  plane(const vec3 &n, real d, material *matl) : normal(n), distance(d), mat(matl) {}
      virtual bool hit(const ray& r, real tmin, real tmax, hit_record &record) const override;

   private:
      vec3 normal;
      real distance;
	  material *mat;
};

bool plane::hit(const ray& r, real tmin, real tmax, hit_record &record) const
{
	//Np + d = 0
	// 

	real denom = dot(normal, r.direction);
	if(abs(denom) > DBL_EPSILON)
	{
		real t = (-distance * dot(normal, r.origin)) / denom;
		if (t > tmin && t < tmax)
		{
			record.n = normal;
			record.p = r.point_at_parameter(t);
			record.t = t;
			record.mat = mat;
			return true;
		}
	}
   return false;
}
