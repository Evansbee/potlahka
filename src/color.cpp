#include "color.h"

#include <xmmintrin.h>


uint32_t Color::U32_RGBA() const
{
	return 0;
}
uint32_t Color::U32_ABGR() const
{
	return 0;
	/*
	__m128 sized = _mm_mul_ps(w,_mm_set_ps1(255.99f));
	__m64 u = _mm_cvtps_pi8(sized);
	uint32_t abgr = u.m64_u32[0];
	*/
}

void Color::GammaCorrect()
{

}

void Color::Contribute(const Color &partial_color, float amount)
{
	__m128 adj = _mm_mul_ps(partial_color.w, _mm_load_ps1(&amount));
	w = _mm_add_ps(w, adj);
}