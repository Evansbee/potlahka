#include <random>
#include <chrono>
#include <limits>
#include "random.hpp"

vec3 random_direction()
{
	vec3 v = random_in_unit_sphere();
	v.make_unit();
	return v;
}
vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0 * vec3(random_range(), random_range(), random_range()) - vec3(1.0, 1.0, 1.0);
	} while (p.length_squared() >= 1.0);
	return p;
}

real random_range(real lower, real upper)
{
	// ret = [lower, upper)
	static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::default_random_engine generator(seed);
	std::uniform_real_distribution<real> distribution(lower, upper);
	return distribution(generator);
}