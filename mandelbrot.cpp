#include <stdio.h>

#include "mandelbrot.hpp"


/* @filename Name of the output file
 * writes the computed mandelbrot set 
 * pixel values to a .tga file
 */
void mandelbrot::output_image(const char *filename)
{
    std::ofstream output_file(filename, std::ofstream::binary);
	
    // create the .tga file header
    std::uint8_t header[18] = {
        0, // No image ID
        0, // No colour map
        2, // Uncompressed 24-bit image
        0, 0, 0, 0, 0, // Empty colour map specification
        0, 0, // X origin
        0, 0, // Y origin
        static_cast<std::uint8_t>(this->width & 0xFF), static_cast<std::uint8_t>((this->width >> 8) & 0xFF), // Width
        static_cast<std::uint8_t>(this->height & 0xff), static_cast<std::uint8_t>((this->height >> 8) & 0xff), // Height
        24, // Bits per pixel
        0, // Image descriptor
    };
    // write the prev created header to the file
    output_file.write((const char *)header, 18);

    // loop width*height iterations
    for (int i=0; i < this->width*this->height; ++i)
    {
        // use bit shifting to properly allocate colours per pixel
        uint8_t pixel[3] = {
            // Colour Channels : 0xRRGGBB
            (uint8_t) (image[i] & 0xFF), // blue channel
            (uint8_t) ((image[i] >> 8) & 0xFF), // green channel
            (uint8_t) ((image[i] >> 16) & 0xFF), // red channel
        };
        // write pixel to file
        output_file.write((const char *)pixel, 3);
    }
    
}


/* Computes the mandelbrot set values
 * Also assigns a colour value to each pixel
 */
void mandelbrot::compute_mandelbrot()
{
    for (int i=0; i < this->width*this->height; ++i)
    {
        int x = (int) (i % this->width);
        int y = (int) (i / this->width);

        std::complex<double> complex_coords((x - (this->scale * this->width))/(this->width/4.0),
                                            (y - (this->width/4.0))/(this->width/4.0));
        std::complex<double> z(0.0, 0.0);

        int iterations = {0};
        while (std::abs(z) < 2.0 && iterations < MAX_ITERATIONS)
        {
            z = (z * z) + complex_coords;
            iterations++;
        }

        if (iterations == MAX_ITERATIONS)
        {
            image[x + this->width*y] = 0xFFFFFF;
        } else
            image[x + this->width*y] = 0x000000;
    }
}

void mandelbrot::create_mandelbrot()
{
    printf("Computing mandelbrot...\n");

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    this->compute_mandelbrot();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    printf("Time taken: %li ms\n", duration);

    this->output_image("output.tga");
}
