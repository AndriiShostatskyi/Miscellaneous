#pragma once

#include <complex>

struct Mandelbrot {
    static const int MAX_ITERATIONS = 1000;

    static int getIterations(double x, double y)
    {
        std::complex<double> z = 0;
        std::complex<double> c(x, y);

        int iterations = 0;

        while (iterations < MAX_ITERATIONS) {
            z = z * z + c;

            if (std::abs(z) > 2) {
                break;
            }

            ++iterations;
        }

        return iterations;
    }
};
