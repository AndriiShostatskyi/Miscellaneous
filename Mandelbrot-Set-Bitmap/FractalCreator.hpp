#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cassert>

#include "ZoomList.hpp"
#include "Mandelbrot.hpp"
#include "Bitmap.hpp"
#include "RGB.hpp"

class FractalCreator {
public:
    FractalCreator(int width, int height);
    void run(std::string name);
    void addZoom(const Zoom& zoom);
    void addRange(double rangeEnd, const RGB& rgb);
    int getRange(int iterations) const;

private:
    void calculateRangeTotals();
    void calculateTotalIterations();
    void calculateIteration();
    void drawFractal();
    void writeBitmap(std::string name);

    int m_width;
    int m_height;

    int total{ 0 };

    std::unique_ptr<int[]> histogram;
    std::unique_ptr<int[]> fractal;

    Bitmap bitmap;
    ZoomList zoomList;

    std::vector<int> ranges;
    std::vector<int> rangeTotals;
    std::vector<RGB> colors;

    bool gotFirstRange{ false };
};
