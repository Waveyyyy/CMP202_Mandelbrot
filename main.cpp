#include <stdio.h>
#include <iostream>

#include "mandelbrot.hpp"


/* @msg message to display to console
 * 
 * Takes an input from a user 
 * and ensures it is of type integer
 */
int input_int(const char *msg, int dfault)
{
    unsigned int_value = {};
    std::string input;

    std::printf("%s", msg);
    std::getline(std::cin, input);
    std::stringstream usrInput(input);
    if(usrInput >> int_value)
        return int_value;

    return dfault;
}


int main()
{
    int width = input_int("Enter a width (Default 1920) : ", 1920);
    int height = input_int("Enter a height (Default 1080) : ", 1080);
    mandelbrot mb = mandelbrot(width, height);

    // run create mandelbrot function
    mb.create_mandelbrot();

    return 0;
}
