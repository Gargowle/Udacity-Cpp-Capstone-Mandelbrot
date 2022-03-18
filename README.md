# CPPND: Capstone Repo : Generate images of the Mandelbrot set

This repository contains the code of a Mandelbrot set image generator as created for the final project of the Udacity C++ Nanodegree program.

The code was written along [this explanation](https://solarianprogrammer.com/2013/02/28/mandelbrot-set-cpp-11/) on how to generate Mandelbrot images, as suggested as one option by the project description, and some code was directly adapted from it. Furthermore, large parts of the code were refactored and multi-threading support was added to the program.

Now towards the official criteria and how this code base fulfills them:
* This project is of type "Option 1".
* A Readme is provided (this very file).
* The code compiles and runs without errors.
* The application satisfies at least five criteria of the rest of the rubric. For example the following criteria:
  * The project reads data from a file and process the data, or the program writes data to a file: The program output is the file `mandelbrot.png`.
  * Classes use appropriate access specifiers for class members: The only class in the project `window` fulfills this.
  * Class constructors utilize member initialization lists: The only class in the project `window` fulfills this.
  * Templates generalize functions in the project: The whole class `window` is templated and accordingly, all members (variables and functions alike) adhere to the template.
  * The project makes use of references in function declarations: For example the function `fractal` declared in line 13 of `functions.h`.
  * The project uses multithreading: The image generation process is multithreaded, see in particular line 72 of `functions.cpp`.


## Dependencies for Running Locally
* cmake >= 3.1
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* FreeImage >= 3.17
  * Linux: [click here for installation instructions](https://codeyarns.com/tech/2014-02-11-how-to-install-and-use-freeimage.html)
  * Mac: [click here for installation instructions](https://formulae.brew.sh/formula/freeimage)
  * Windows: [click here for installation instructions](https://freeimage.sourceforge.io/download.html)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Mandelbrot`.
5. An image is created. On a linux system view it with `xdg-open mandelbrot.png`

## Short overview over the code structure:
* `window.h` contains the class `window`, which is used as a data container for storing meta information (dimensions) of the sampled complex plane.
* `functions.h` and `functions.cpp` contains all functions used for sampling the polynomial defining the Mandelbrot set in the complex plane.
* `plot.h` and `plot.cpp` contains all functionality with regards to converting the sampled values to RGB space and image output functionality.
* `main.cpp` contains the main function (without any particular logic except for invoking `mandelbrot()` as defined in `functions.cpp`).