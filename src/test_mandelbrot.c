#include <stdint.h>
#include <stdio.h>

#include "mandelbrot.h"

/* Convert a real value to Q16.16 fixed point (integer = value * 65536). */
#define Q16_16(v) ((int32_t)((v) * 65536.0))

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

    return 0;
}
