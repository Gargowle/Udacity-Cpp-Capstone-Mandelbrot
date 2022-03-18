#include <thread>
#include <future>
#include <tuple>
#include "functions.h"
#include "plot.h"

// constants
constexpr int WINDOW_SIZE_X = 1200;
constexpr int WINDOW_SIZE_Y = 1200;

constexpr double DOMAIN_X_MIN = -2.2;
constexpr double DOMAIN_X_MAX = 1.2;
constexpr double DOMAIN_Y_MIN = -1.7;
constexpr double DOMAIN_Y_MAX = 1.7;

constexpr double INFINITY_THRESHOLD = 2.0;
constexpr int MAX_ITERATIONS = 500;


void mandelbrot()
{
	// Chreate window with desired size
	window<int> scr(0, WINDOW_SIZE_X, 0, WINDOW_SIZE_Y);

	// Domain in which we test for points ("image section")
	window<double> fract(DOMAIN_X_MIN, DOMAIN_X_MAX, DOMAIN_Y_MIN, DOMAIN_Y_MAX);

	// Function used to calculate the fractal
	// Mandelbrot set is defined by function C -> C ; z -> z^2 + c   with c elem C is a parameter
	auto func = [](std::complex<double> z, std::complex<double> c) -> std::complex<double> {return z * z + c; };

	const char* fname = "mandelbrot.png";
	std::vector<std::vector<int>> colors;

	fractal(scr, fract, MAX_ITERATIONS, colors, func, fname);
}


void fractal(
	window<int>& scr,
	window<double>& fract,
	int iter_max,
	std::vector<std::vector<int>>& colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func,
	const char* fname
)
{
	get_number_iterations(scr, fract, iter_max, colors, func);

	plot(scr, colors, iter_max, fname);	
}


void get_number_iterations(
	window<int>& scr,
	window<double>& fract,
	int iter_max,
	std::vector<std::vector<int>>& colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func
)
{
	std::vector<std::tuple<int, int, int>> slices = get_best_possible_split(scr);

	std::vector<std::future<std::vector<int>>> thread_pool;

	for (std::tuple<int, int, int>& slice : slices)
	{
		int row_min = std::get<0>(slice);
		int row_max = std::get<1>(slice);
		//int already_covered_pixels = std::get<2>(slice);

		thread_pool.emplace_back(std::async(get_image_slice, scr.width(), scr.height(), scr.x_min(), fract.width(), fract.height(), fract.x_min(), fract.y_min(), row_min, row_max, iter_max, func));
	}

	for (std::future<std::vector<int>>& thread : thread_pool)
	{
		colors.emplace_back(thread.get());
	}	
}


std::vector<std::tuple<int, int, int>> get_best_possible_split(window<int>& scr)
{
	int nr_threads = std::thread::hardware_concurrency();
	int slice_thickness = scr.height() / nr_threads;
	int leftover_rows = scr.height() % nr_threads;

	std::vector<std::tuple<int, int, int>> slices;
	int row_min;
	int row_max = scr.y_min();
	int already_covered_pixels = 0;
	for (int thread_index = 0; thread_index < nr_threads; ++thread_index)
	{
		int row_min = row_max;
		row_max += slice_thickness;

		// some threads might need to take care of an extra row
		if (leftover_rows > 0)
		{
			--leftover_rows;
			row_max += 1;
		}

		slices.emplace_back(std::tuple<int, int, int>(row_min, row_max, already_covered_pixels));

		already_covered_pixels += (row_max - row_min) * scr.width();
	}

	return slices;
}


std::vector<int> get_image_slice(
	int scr_width,
	int scr_height,
	int scr_x_min,
	double fr_width,
	double fr_height,
	double fr_x_min,
	double fr_y_min,
	int slice_y_min,
	int slice_y_max,
	//int already_covered_pixels,
	int iter_max,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func
)
{
	std::vector<int> image_slice(scr_width * (slice_y_max - slice_y_min));

	int k = 0;
	for (int i = slice_y_min; i < slice_y_max; ++i)
	{
		for (int j = scr_x_min; j < scr_x_min + scr_width; ++j)
		{
			std::complex<double> c(static_cast<double>(j), static_cast<double>(i));
			c = scale(scr_width, scr_height, fr_width, fr_height, fr_x_min, fr_y_min, c);
			image_slice[k] = escape(c, iter_max, func);
			++k;
		}
	}

	return image_slice;
}


std::complex<double> scale(
	int scr_width,
	int scr_height,
	double fr_width,
	double fr_height,
	double fr_x_min,
	double fr_y_min,
	std::complex<double> c
)
{
	double real = c.real() / static_cast<double>(scr_width) * fr_width + fr_x_min;
	double imag = c.imag() / static_cast<double>(scr_height) * fr_height + fr_y_min;

	return std::complex<double>(real, imag);
}


int escape(
	std::complex<double> c,
	int iter_max,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func
)
{
	// initialize z with zero
	std::complex<double> z(0);

	int iter = 0;

	while(abs(z) < INFINITY_THRESHOLD
		&& iter < iter_max)
	{
		z = func(z, c);
		iter++;
	}

	return iter;
}