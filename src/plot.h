#ifndef PLOT_H
#define PLOT_H

#include <tuple>
#include <vector>
#include "window.h"


// map single scalar value into rgb range
std::tuple<int, int, int> get_rgb(int n, int iter_max);

// plot values to png
void plot(window<int>& scr, std::vector<int>& colors, int iter_max, const char* fname);

#endif