#pragma once


#include "config.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "random.hpp"
#include "ray.hpp"

class material
{
public:
	virtual bool scatter(const ray &ray_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const vec3& albedoIn) : m_Albedo(albedoIn) {}
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 target = rec.p + rec.n + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = m_Albedo;
		return true;
	}
private:
	vec3 m_Albedo;
};
	
class metal : public material
{
public:
	metal(const vec3& albedoIn, real fuzz = 0.0) : m_Albedo(albedoIn), m_Fuzziness(fuzz) {}
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 reflected = reflect(unit_vector(ray_in.direction), rec.n);
		scattered = ray(rec.p, reflected + m_Fuzziness * random_in_unit_sphere());
		attenuation = m_Albedo;
		return (dot(scattered.direction, rec.n) > 0);
	}
private:
	vec3 m_Albedo;
	real m_Fuzziness;
};

class emissive : public material
{
public:
	emissive(const vec3& albedoIn) : m_Albedo(albedoIn) {}
	virtual bool scatter(const ray& ray_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		vec3 target = rec.p + rec.n + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = m_Albedo;
		return true;
	}
private:
	vec3 m_Albedo;
};




