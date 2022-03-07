#include <stdio.h>
#include <iostream>

#include "mandelbrot.hpp"


/* @msg message to display to console
 * 
 * Takes an input from a user 
 * and ensures it is of type integer
 */
int input_int(const char *msg)
{
    bool valid = {0};
    unsigned int_value = {};
    std::string input;

    do
    {
        std::printf("%s", msg);
        std::getline(std::cin, input);
        std::stringstream usrInput(input);
        if(usrInput >> int_value)
            valid = 1;
    } while (!valid);

    return int_value;
}


int main()
{
    std::printf("Change resolution (Default 1920x1080)? [y/N] ");
    char ans = tolower(std::getchar());
    if (!(ans == '\n'))
        std::getchar();
    // default constructor
    mandelbrot mb; 

    // if user chooses custom resolution
    // take input for width/height
    // create object with supplied width/height
    if(ans == 'y')
    {
        int width = {0};
        int height = {0};

        width = input_int("Enter a width (Default 1920) : ");
        height = input_int("Enter a height (Default 1080) : ");
        mandelbrot mb(width, height);
    }

    // run create mandelbrot function
    mb.create_mandelbrot();

    return 0;
}
