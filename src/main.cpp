// raytrace.cpp : Defines the entry point for the console application.
//


#include <cstdlib>
#include <cstdint>
#include <iostream>
#include "image.hpp"
#include "vec3.hpp"
#include "ray.hpp"

float hit_sphere(const vec3f& center, float rad, const rayf &r)
{
	vec3f oc = r.origin - center;
	float a = dot(r.direction, r.direction);
	float b = 2.f * dot(oc, r.direction);
	float c = dot(oc, oc) - rad * rad;
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}


vec3f color(const rayf &r)
{
	float t = hit_sphere(vec3f(0, 0, -1), .25, r);
	if (t > 0.0)
	{
		vec3f N = unit_vector(r.point_at_parameter(t) - vec3f(0, 0, -1));
		return 0.5f * vec3f(N.x + 1, N.y + 1, N.z + 1);
	}

	t = hit_sphere(vec3f(1, 0, -1), .25, r);
	if (t > 0.0)
	{
		vec3f N = unit_vector(r.point_at_parameter(t) - vec3f(1, 0, -1));
		return 0.5f * vec3f(N.x + 1, N.y + 1, N.z + 1);
	}

	vec3f unit_direction = unit_vector(r.direction);
	float ot = 0.5 * (unit_direction.y + 1.0);
	return (1.0f - ot) * vec3f(1.0, 1.0, 1.0) + ot * vec3f(0.5, 0.5, 1.0);
}

int main()
{
	Image img = AllocateImage(800, 400);


	vec3f lower_left_corner(-2.0, -1.0, -1.0);
	vec3f horizontal(4.0, 0.0, 0.0);
	vec3f vertical(0.0, 2.0, 0.0);
	vec3f origin(0.0, 0.0, 0.0);

	int sample_cnt = 0;

	for (int y = img.Height - 1; y >= 0; y--)
	{
		for (int x = 0; x < img.Width; ++x)
		{
			sample_cnt++;
			if (sample_cnt % 10000 == 0)
			{
				std::cout << "\rSamples: " << sample_cnt;
			}
			float u = (float)x / (float)img.Width;
			float v = (float)y / (float)img.Height;
			rayf r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3f c = color(r);

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

