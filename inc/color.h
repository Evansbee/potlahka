#pragma once

#include <cstdint>
#include <xmmintrin.h>

class Color
{
public:
	Color() : Color(0.0,0.0,0.0,1.0) {}
	Color(float red, float green, float blue) : Color(red, green, blue, 1.0) {}
	Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {}
	uint32_t U32_RGBA() const;
	uint32_t U32_ABGR() const;

	void GammaCorrect();
	void Contribute(const Color &partial_color, float amount);
	 
	union
	{
		float d[4];
		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
		__m128 w;
	};
};