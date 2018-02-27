#pragma once

#include <cstdint>
#include "vec3.hpp"

struct Image
{
	uint32_t Width;
	uint32_t Height;
	uint32_t *Pixels;
};

Image AllocateImage(uint32_t width, uint32_t height);
uint32_t GetPixelSize(Image img);
void WriteImage(const char *filename, Image img, bool invert_y = false);

uint32_t RealToBGRA(const vec3& in, bool gamma_correct = true);

