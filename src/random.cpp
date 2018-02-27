#include <random>
#include <chrono>
#include <limits>
#include "random.hpp"

vec3 random_direction()
{
	vec3 v(random_range(-1.0, 1.0), random_range(-1.0, 1.0), random_range(-1.0, 1.0));
	while(v.length_squared() >= 1.0)
	{
		v = vec3(random_range(-1.0, 1.0), random_range(-1.0, 1.0), random_range(-1.0, 1.0));
	}
	v.make_unit();
	return v;
}

real random_range(real lower, real upper)
{
	// ret = [lower, upper)
	static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	static std::default_random_engine generator(seed);
	std::uniform_real_distribution<real> distribution(lower, upper);
	return distribution(generator);
}