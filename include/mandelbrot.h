#ifndef FRACTAL_MANDELBROT_H
#define FRACTAL_MANDELBROT_H

#include <stdint.h>

uint8_t mandelbrot_pixel(int32_t c_real, int32_t c_imag, uint32_t max_iterations);

#endif /* FRACTAL_MANDELBROT_H */
