#pragma once

#include "config.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include "hittable.hpp"

class plane : public hittable
{
   public:
      plane() {}
      plane(const vec3 &n, real d) : normal(n), distance(d) {}
      virtual bool hit(const ray& r, real tmin, real tmax, hit_record &record) const override;

   private:
      vec3 normal;
      real distance;
};

bool plane::hit(const ray& r, real tmin, real tmax, hit_record &record) const
{
   return false;
}
