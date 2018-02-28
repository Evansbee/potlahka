// raytrace.cpp : Defines the entry point for the console application.
//


#include <cstdlib>
#include <cstdint>
#include <iostream>
#include "image.hpp"
#include "vec3.hpp"
#include "plane.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "random.hpp"
#include <vector>

std::vector<hittable*> hittables;
vec3 color(const ray &r)
{
	hit_record h;
	real max = 1000.0;
	bool any_hit = false;
	for (auto &s : hittables)
	{
		if (s->hit(r, 0.0, max, h))
		{
			any_hit = true;
			max = h.t;
		}
	}
	if (any_hit)
	{
		return 0.5f * vec3(h.n.x + 1, h.n.y + 1, h.n.z + 1);
	}
	

	vec3 unit_direction = unit_vector(r.direction);
	float ot = 0.5 * (unit_direction.y + 1.0);
	return (1.0f - ot) * vec3(1.0, 1.0, 1.0) + ot * vec3(0.5, 0.5, 1.0);
}

int main()
{
	Image img = AllocateImage(800, 400);

	for (auto i = 0; i < 50; i++)
	{
		hittables.push_back(new sphere(vec3(random_range(-10.0, 10.0), random_range(-10.0, 10.0), random_range(-10.0, -2.0)), random_range(0, 2.0)));
	}
	hittables.push_back(new plane(vec3(0, 1, 0), -2.0));
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vertical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	int sample_cnt = 0;

	for (int y = img.Height - 1; y >= 0; y--)
	{
		for (int x = 0; x < img.Width; ++x)
		{
			sample_cnt++;
			if (sample_cnt % 10000 == 0)
			{
				std::cout << "\rSamples: " << sample_cnt << std::flush;
			}
			float u = (float)x / (float)img.Width;
			float v = (float)y / (float)img.Height;
			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 c = color(r);

			uint32_t red = (uint8_t)(c[0] * 255.99) << 16;
			uint32_t green = (uint8_t)(c[1] * 255.99) << 8;
			uint32_t blue = (uint8_t)(c[2] * 255.99);

			img.Pixels[x + y * img.Width] = 0xFF000000 | red | green | blue;
		}
	}
	std::cout << std::endl;
	WriteImage("test.bmp", img);

	return 0;
}

