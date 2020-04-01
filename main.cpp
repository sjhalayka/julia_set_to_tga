// Code by: Shawn Halayka -- sjhalayka@gmail.com
// Code is in the public domain


#include "main.h"


int main(int argc, char **argv)
{
    const size_t res = 3000;

    const float x_grid_max = 1.5;
    const float x_grid_min = -x_grid_max;
    const size_t x_res = res;
    const complex<float> x_step_size((x_grid_max - x_grid_min) / (x_res - 1), 0);

    const float y_grid_max = 1.5;
    const float y_grid_min = -y_grid_max;
    const size_t y_res = res;
    const complex<float> y_step_size(0, (y_grid_max - y_grid_min) / (y_res - 1));

    const complex<float> C(0.2f, 0.5f);
    const unsigned short int max_iterations = 8;
    const float threshold = 4.0f;

    float_grayscale luma;
    luma.px = x_res;
    luma.py = y_res;
    luma.pixel_data.resize(static_cast<size_t>(luma.px)* static_cast<size_t>(luma.py));

    // Too small
    if (luma.px < 3 || luma.py < 3)
    {
        cout << "Template must be at least 3x3 pixels in size." << endl;
        return 2;
    }

    // Not square
    if (luma.px != luma.py)
    {
        cout << "Template must be square." << endl;
        return 3;
    }
    
    // Calculate Julia set
    complex<float> Z(x_grid_min, y_grid_min);

    for (size_t x = 0; x < x_res; x++, Z += x_step_size)
    {
        Z = complex<float>(Z.real(), y_grid_min);

        for (size_t y = 0; y < y_res; y++, Z += y_step_size)
        {
            size_t float_index = y * x_res + x;

            float f = iterate_2d(Z, C, max_iterations, threshold);

            // Truncate
            if (f > threshold)
                f = threshold;

            // Normalize
            f /= threshold;

            // Invert
            f = 1 - f;

            luma.pixel_data[float_index] = f;
        }
    }

	write_float_grayscale_to_tga("out.tga", luma);

	return 0;
}

