#include "plot.h"
#include <FreeImage.h>


std::tuple<int, int, int> get_rgb(int n, int iter_max)
{
	// map value n to the interval [0, 1]
	double t = static_cast<double>(n) / static_cast<double>(iter_max);

	// use modified Bernstein polynomials for mapping scalar value into rgb range
	int r = static_cast<int>(  9 * (1 - t) *       t *       t * t * 255);
	int g = static_cast<int>( 15 * (1 - t) * (1 - t) *       t * t * 255);
	int b = static_cast<int>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);

	return std::tuple<int, int, int>(r, g, b);
}


void plot(window<int>& scr, std::vector<int>& colors, int iter_max, const char* fname)
{
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif

	unsigned int width = scr.width();
	unsigned int height = scr.height();

	FIBITMAP* bitmap = FreeImage_Allocate(width, height, 32); // four 8 bit channels RBGA

	int k = 0;
	std::tuple<int, int, int> rgb;

	for(int i = scr.y_min(); i < scr.y_max(); ++i)
	{
		for(int j = scr.x_min(); j < scr.x_max(); ++j)
		{
			int n = colors[k];

			rgb = get_rgb(n, iter_max);

			RGBQUAD	col;
			col.rgbRed = std::get<0>(rgb);
			col.rgbGreen = std::get<1>(rgb);
			col.rgbBlue = std::get<2>(rgb);
			col.rgbReserved = 255;

			// set color of this one pixel
			FreeImage_SetPixelColor(bitmap, j, i, &col);

			k++;
		}
	}

	// save image to disk
	FreeImage_Save(FIF_PNG, bitmap, fname, PNG_DEFAULT);

	// release memory
	FreeImage_Unload(bitmap);

#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialize();
#endif
	
}
