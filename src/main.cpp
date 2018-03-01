// raytrace.cpp : Defines the entry point for the console application.
//

#include <cfloat>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "image.hpp"
#include "vec3.hpp"
#include "plane.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include "hittable.hpp"
#include "random.hpp"
#include "camera.hpp"
#include "material.hpp"

std::vector<hittable*> hittables;
uint64_t rays = 0;

vec3 color(const ray &r, int depth = 0)
{
	hit_record h;
	real max = DBL_MAX;
	bool any_hit = false;
	for (auto &s : hittables)
	{
		rays++;
		if (s->hit(r, 0.001, max, h))
		{
			any_hit = true;
			max = h.t;
		}
	}
	if (any_hit)
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && h.mat->scatter(r, h, attenuation, scattered))
		{
			return attenuation * color(scattered, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}


	vec3 unit_direction = unit_vector(r.direction);
	real ot = 0.5 * (unit_direction.y + 1.0);
	return (1.0f - ot) * vec3(1.0, 1.0, 1.0) + ot * vec3(.5,.7,1);
}

int main(int argc, char** argv)
{
	Image img = AllocateImage(400, 200);
	auto start_time = clock();
	hittables.push_back(new sphere(vec3(0, 0, -1), .5, new lambertian(vec3(random_range(), random_range(), random_range()))));

	hittables.push_back(new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(random_range(), random_range(), random_range()))));

	hittables.push_back(new sphere(vec3(1, 0, -1), random_range(), new metal(vec3(random_range(), random_range(), random_range()),random_range())));

	hittables.push_back(new sphere(vec3(-1, 0, -1), random_range(), new metal(vec3(random_range(), random_range(), random_range()), random_range())));

	int32_t last_percent = -1;
	
	camera c(vec3(0.0,0.0,0.0),vec3(),75.0,2.0); //camera(const vec3& position, const vec3& lookAt, real FoV, real AspectRatio))
	int num_samples = 32;
	if (argc == 2 )
	{
		num_samples = std::stol(std::string(argv[1]));
	}
	

	for (int y = img.Height - 1; y >= 0; y--)
	{
		for (int x = 0; x < img.Width; ++x)
		{
			vec3 out_color;
			for (auto s = 0; s < num_samples; s++)
			{
				real u = ((real)x + random_range(0,1))/ (real)img.Width;
				real v = ((real)y + random_range(0,1))/ (real)img.Height;

				ray r = c.GetRay(u,v);
				out_color += color(r)/(real)num_samples;
			}
			out_color = vec3(sqrt(out_color.r), sqrt(out_color.g), sqrt(out_color.b));
			uint32_t red = (uint8_t)(out_color[0] * 255.99) << 16;
			uint32_t green = (uint8_t)(out_color[1] * 255.99) << 8;
			uint32_t blue = (uint8_t)(out_color[2] * 255.99);

			img.Pixels[x + y * img.Width] = 0xFF000000 | red | green | blue;
		}
		int32_t this_pcnt = (100 * (img.Height - y) / img.Height);
		if(this_pcnt > last_percent && this_pcnt % 5 == 0)
		{
			auto this_time = clock();
			last_percent = this_pcnt;
			std::cout << "[INFO] " << 100 * (img.Height - y) / img.Height << "% Complete ("<<(this_time-start_time)/(CLOCKS_PER_SEC/1000)<<"ms)\n";
		}
		
	}
	auto end_time = clock();
	auto elapsed_time = end_time - start_time;
	std::cout << "[INFO] Raytraced image in " << elapsed_time /(CLOCKS_PER_SEC/1000) << "ms\n";
	std::cout << "[INFO] Cast " << rays << " rays\n";
	std::cout << "[INFO] Performance: " << rays / (elapsed_time / (CLOCKS_PER_SEC/1000))  << " rays/ms\n";
	WriteImage("test.bmp", img);
	std::cout << "Waiting for keypress to exit...\n";
	static_cast<void>(std::getchar());
	return 0;
}

