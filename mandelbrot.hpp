#ifndef MANDLEBROT_IMPROVED_MANDLEBROT_HPP
#define MANDLEBROT_IMPROVED_MANDLEBROT_HPP

#include <cstdlib>
#include <complex>
#include <stdint.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>


class mandelbrot
{
    int width = {0};
    int height = {0};
    const int MAX_ITERATIONS = 1000;
    uint32_t *image;
    double scale = 0.75;


    void output_image(const char *filename);
    void compute_mandelbrot();

public:
    void create_mandelbrot();

    // Allows user to choose resolution
    mandelbrot(int width, int height): width(width), height(height)
    {
        // Image resolution
        this->image = new uint32_t[height*width];
    }

    // Default constructor
    mandelbrot(): mandelbrot(1920,1080){}

};


#endif
