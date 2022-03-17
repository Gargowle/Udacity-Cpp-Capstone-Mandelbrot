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
	std::vector<int> colors(scr.size());

	fractal(scr, fract, MAX_ITERATIONS, colors, func, fname);
}


void fractal(
	window<int>& scr,
	window<double>& fract,
	int iter_max,
	std::vector<int>& colors,
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
	std::vector<int>& colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func
)
{
	int k = 0;
	for (int i = scr.y_min(); i < scr.y_max(); ++i)
	{
		for (int j = scr.x_min(); j < scr.x_max(); ++j)
		{
			std::complex<double> c(static_cast<double>(j), static_cast<double>(i));
			c = scale(scr, fract, c);
			colors[k] = escape(c, iter_max, func);
			++k;
		}
	}
}


std::complex<double> scale(
	window<int>& scr,
	window<double>& fr,
	std::complex<double> c
)
{
	double real = c.real() / static_cast<double>(scr.width()) * fr.width() + fr.x_min();
	double imag = c.imag() / static_cast<double>(scr.height()) * fr.height() + fr.y_min();

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