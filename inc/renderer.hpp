#pragma once

#include <vector>
#include <cstdint>

struct RenderChunk
{
	uint32_t StartX;
	uint32_t StartY;
	uint32_t Width;
	uint32_t Height;
};

struct RenderQueue
{
	std::vector<RenderChunk> Chunks;
};