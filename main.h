// Code by: Shawn Halayka -- sjhalayka@gmail.com
// Code is in the public domain


#ifndef MAIN_H
#define MAIN_H


#include "image.h"


#include <cmath>
#include <complex>
using namespace std;


inline float iterate_julia(
    complex<float> Z,
    const complex<float> C,
    const short unsigned int max_iterations,
    const float threshold)
{
    for (short unsigned int i = 0; i < max_iterations; i++)
    {
        Z = Z * Z + C;

        if (abs(Z) >= threshold)
            break;
    }

    return abs(Z);
}


#endif