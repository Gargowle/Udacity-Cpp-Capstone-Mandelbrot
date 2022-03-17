#ifndef WINDOW_H
#define WINDOW_H

template <typename T>
class window
{
public:
	// constructor
	window(T x_min, T x_max, T y_min, T y_max)
		: _x_min(x_min), _x_max(x_max), _y_min(y_min), _y_max(y_max)
	{}

	// Getters
	T x_min() const { return _x_min; }
	T x_max() const { return _x_max; }
	T y_min() const { return _y_min; }
	T y_max() const { return _y_max; }

	// Utility functions for getting window information
	T size() { return width() * height(); }
	T width() { return _x_max - _x_min; }
	T height() { return _y_max - _y_min; }

private:
	T _x_min;
	T _x_max;
	T _y_min;
	T _y_max;
};

#endif