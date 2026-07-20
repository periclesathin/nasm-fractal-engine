#include <stdint.h>
#include <stdio.h>

#include "mandelbrot.h"

/* Convert a real value to Q16.16 fixed point (integer = value * 65536). */
#define Q16_16(v) ((int32_t)((v) * 65536.0))

/* Draw the set as ASCII: scan a grid of points and map iterations to a char. */
static void draw_ascii(void) {
    const int cols = 70;
    const int rows = 24;
    const uint32_t max_iterations = 100;
    const char *ramp = " .:-=+*#%@";  /* few iterations -> sparse, many -> dense */
    const int levels = 10;

    /* view window in the complex plane */
    const double re_min = -2.5, re_max = 1.0;
    const double im_min = -1.15, im_max = 1.15;

    for (int row = 0; row < rows; row++) {
        double im = im_min + (im_max - im_min) * row / (rows - 1);
        for (int col = 0; col < cols; col++) {
            double re = re_min + (re_max - re_min) * col / (cols - 1);
            uint8_t iters = mandelbrot_pixel(Q16_16(re), Q16_16(im), max_iterations);
            putchar(ramp[iters * (levels - 1) / max_iterations]);
        }
        putchar('\n');
    }
}

int main(void) {
    const uint32_t max_iterations = 100;

    struct {
        const char *name;
        double re;
        double im;
    } points[] = {
        {"origin (0, 0)            [inside]", 0.0, 0.0},
        {"(-1, 0)                  [inside]", -1.0, 0.0},
        {"(-0.5, 0)                [inside]", -0.5, 0.0},
        {"(0.25, 0) cusp          [inside]", 0.25, 0.0},
        {"(0.35, 0)               [outside]", 0.35, 0.0},
        {"(1, 0)                  [outside]", 1.0, 0.0},
        {"(2, 0)                  [outside]", 2.0, 0.0},
        {"(-0.75, 0.1) boundary          ", -0.75, 0.1},
        {"(0.3, 0.5)                     ", 0.3, 0.5},
    };
    const size_t n = sizeof(points) / sizeof(points[0]);

    printf("mandelbrot_pixel (Q16.16), max_iterations = %u\n", max_iterations);
    printf("---------------------------\n");
    for (size_t i = 0; i < n; i++) {
        uint8_t iters = mandelbrot_pixel(Q16_16(points[i].re),
                                         Q16_16(points[i].im),
                                         max_iterations);
        printf("%-34s -> %3u\n", points[i].name, (unsigned)iters);
    }

    printf("\nMandelbrot set:\n");
    draw_ascii();

    return 0;
}
