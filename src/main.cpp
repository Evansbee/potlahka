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

#include <thread>
#include <mutex>


vec3 color(const ray &r, int depth = 0);


struct chunk
{
	uint32_t startx;
	uint32_t starty;
	uint32_t width;
	uint32_t height;
	Image *image;
	camera *cam;
	std::vector<hittable*> *world;
};

std::mutex rays_mutex;


void render_section(chunk c)
{
	const int num_samples = 64;
	for (int y = c.starty; y < c.starty + c.height; ++y)
	{
		for (int x = c.startx; x < c.startx + c.width; ++x)
		{
			vec3 out_color;
			for (auto s = 0; s < num_samples; s++)
			{
				real u = ((real)x + random_range(0, 1)) / (real)c.image->Width;
				real v = ((real)y + random_range(0, 1)) / (real)c.image->Height;

				ray r = c.cam->GetRay(u, v);
				out_color += color(r) / (real)num_samples;
			}
			out_color = vec3(sqrt(out_color.r), sqrt(out_color.g), sqrt(out_color.b));
			uint32_t red = (uint8_t)(out_color[0] * 255.99) << 16;
			uint32_t green = (uint8_t)(out_color[1] * 255.99) << 8;
			uint32_t blue = (uint8_t)(out_color[2] * 255.99);

			c.image->Pixels[x + y * c.image->Width] = 0xFF000000 | red | green | blue;
		}
	}
}


std::vector<hittable*> hittables;
uint64_t rays = 0;

vec3 color(const ray &r, int depth)
{
	hit_record h;
	real max = DBL_MAX;
	bool any_hit = false;
	for (auto &s : hittables)
	{
		rays_mutex.lock();
		rays++;
		rays_mutex.unlock();
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
	return (1.0f - ot) * vec3(1.0, 1.0, 1.0) + ot * vec3(.5, .7, 1);
}
std::mutex chunk_access;
void RenderQueueTillEmpty(std::vector<chunk> *chunks)
{
	while (true)
	{
		chunk_access.lock();
		if (chunks->size() > 0)
		{
			std::cout << "[INFO] Chunks Left: " << chunks->size() << " (at thread " << std::this_thread::get_id() << ")\n";
			auto c = chunks->at(chunks->size() - 1);
			chunks->pop_back();
			chunk_access.unlock();
			render_section(c);
		}
		else
		{
			chunk_access.unlock();
			return;
		}
	}
}

int main(int argc, char** argv)
{
	Image img = AllocateImage(800, 400);
	auto start_time = clock();
	hittables.push_back(new sphere(vec3(0, 0, -1), .5, new lambertian(vec3(random_range(), random_range(), random_range()))));

	hittables.push_back(new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(random_range(), random_range(), random_range()))));

	hittables.push_back(new sphere(vec3(1, 0, -1), random_range(), new metal(vec3(random_range(), random_range(), random_range()), random_range())));

	hittables.push_back(new sphere(vec3(-1, 0, -1), random_range(), new metal(vec3(random_range(), random_range(), random_range()), random_range())));

	int32_t last_percent = -1;



	camera *cam = new camera(vec3(0.0, 0.0, 0.0), vec3(), 75.0, 2.0); //camera(const vec3& position, const vec3& lookAt, real FoV, real AspectRatio))
	int num_samples = 32;
	if (argc == 2)
	{
		num_samples = std::stol(std::string(argv[1]));
	}

	std::vector<chunk> chunks;
	
	uint32_t tile_size = 64;
	
	for (int y = 0; y < img.Height + (tile_size - 1); y+=tile_size)
	{
		for (int x = 0; x < img.Width + (tile_size - 1); x+=tile_size)
		{
			chunk c;
			c.startx = x;
			c.starty = y;
			c.cam = cam;
			c.image = &img;
			c.world = &hittables;

			if (y + tile_size < img.Height)
			{
				c.height = tile_size;
			}
			else
			{
				c.height = img.Height - y;
			}
			if (x + tile_size < img.Width)
			{
				c.width = tile_size;
			}
			else
			{
				c.width = img.Width - x;
			}
			chunks.push_back(c);
		}
	}
	std::vector<std::thread> thread_pool;
	std::cout << "[INFO] Starting " << std::thread::hardware_concurrency() << " threads for rendering...\n";
	for (auto i = 1; i < std::thread::hardware_concurrency(); ++i)
	{
		thread_pool.push_back(std::thread(RenderQueueTillEmpty, &chunks));
	}
	RenderQueueTillEmpty(&chunks);
	for (auto &t : thread_pool)
	{
		t.join();
	}
	auto end_time = clock();
	auto elapsed_time = end_time - start_time;
	std::cout << "[INFO] Raytraced image in " << elapsed_time / (CLOCKS_PER_SEC / 1000) << "ms\n";
	std::cout << "[INFO] Cast " << rays << " rays\n";
	std::cout << "[INFO] Performance: " << rays / (elapsed_time / (CLOCKS_PER_SEC / 1000)) << " rays/ms\n";
	WriteImage("test.bmp", img);
	std::cout << "Waiting for keypress to exit...\n";
	static_cast<void>(std::getchar());
	return 0;
}

