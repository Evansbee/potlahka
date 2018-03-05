
#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include "image.hpp"

#pragma pack(push, 1)
struct bitmap_header
{
	uint16_t FileType;
	uint32_t FileSize;
	uint16_t Reserved1;
	uint16_t Reserved2;
	uint32_t BitmapOffset;
	uint32_t Size;
	int32_t  Width;
	int32_t  Height;
	uint16_t Planes;
	uint16_t BitsPerPixel;
	uint32_t Compression;
	uint32_t SizeOfBitmap;
	int32_t  HResolution;
	int32_t  Vresolution;
	uint32_t ColorsUsed;
	uint32_t ColorsImportant;

};
#pragma pack(pop)

Image AllocateImage(uint32_t width, uint32_t height)
{
	Image ret;
	ret.Width = width;
	ret.Height = height;
	ret.Pixels = (uint32_t *)malloc(GetPixelSize(ret));
	return ret;
}

uint32_t GetPixelSize(Image img)
{
	return img.Width * img.Height * sizeof(uint32_t);
}

void WriteImage(const char *filename, Image img, bool invert_y)
{
	bitmap_header bmh = {};

	bmh.FileType = 0x4D42;
	bmh.FileSize = sizeof(bmh) + GetPixelSize(img);

	bmh.BitmapOffset = sizeof(bmh);
	bmh.Size = sizeof(bmh) - 14;
	bmh.Width = img.Width;
	bmh.Height = img.Height;
	if (invert_y)
	{
		bmh.Height = bmh.Height * -1;
	}
	bmh.Planes = 1;
	bmh.BitsPerPixel = 32;
	bmh.Compression = 0;
	bmh.SizeOfBitmap = 0;
	bmh.HResolution = 0;
	bmh.Vresolution = 0;
	bmh.ColorsUsed = 0;
	bmh.ColorsImportant = 0;



	FILE *f = NULL;
#ifdef _WIN32
	if (fopen_s(&f, filename, "wb") == 0)
#else
	if ((f = fopen(filename, "wb")) != NULL)
#endif
	{
		fwrite(&bmh, sizeof(bmh), 1, f);
		fwrite(img.Pixels, GetPixelSize(img), 1, f);
		fclose(f);
	}
	else
	{
		fprintf(stderr, "[ERROR] FAILED TO WRITE OUTPUT FILE\n");
	}
}


uint32_t RealToBGRA(const vec3& in, bool gamma_correct)
{
	if (!gamma_correct)
	{
		
	}
	return 0;
}
