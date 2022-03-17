#ifndef FUNCTIONS_H
#define PFUNCTIONS_H


#include <vector>
#include <complex>
#include <functional>
#include "window.h"


void mandelbrot();

void fractal(
	window<int>& scr,
	window<double>& fract,
	int iter_max,
	std::vector<int>& colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func,
	const char* fname
);

// for each pixel in image check if the point goes to infinity
void get_number_iterations(
	window<int>& scr,
	window<double>& fract,
	int iter_max,
	std::vector<int>& colors,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func
);

// get the complex number equivalent to a given pixel coordinate
std::complex<double> scale(
	window<int>& scr,
	window<double>& fr,
	std::complex<double> c
);

// Check if a point is in the mandelbrot set or if the function goes to infinity; returns number of iterations
int escape(
	std::complex<double> c,
	int iter_max,
	const std::function<std::complex<double>(std::complex<double>, std::complex<double>)>& func
);

#endif