#include "FractalCreator.hpp"

FractalCreator::FractalCreator(int width, int height)
    : m_width{ width }
    , m_height{ height }
    , histogram{ new int[Mandelbrot::MAX_ITERATIONS]{ 0 } }
    , fractal{ new int[m_width * m_height]{ 0 } }
    , bitmap{ m_width, m_height }
    , zoomList{ m_width, m_height }
{
    zoomList.add(Zoom(m_width / 2, m_height / 2, 4.0 / m_width)); // default zoom
}

void FractalCreator::run(std::string name)
{
    std::cout << "Calculating Mandelbrot set..." << std::endl;

    calculateIteration();
    calculateTotalIterations();
    calculateRangeTotals();

    std::cout << "Done. \nDrawing..." << std::endl;

    drawFractal();

    std::cout << "Done. \nWriting to bitmap..." << std::endl;
    writeBitmap(std::move(name));

    std::cout << "Done. \nBitmap is ready!" << std::endl;
}

void FractalCreator::addZoom(const Zoom& zoom)
{
    zoomList.add(zoom);
}

void FractalCreator::addRange(double rangeEnd, const RGB& rgb)
{
    ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    colors.push_back(rgb);

    if (gotFirstRange) {
        rangeTotals.push_back(0);
    }

    gotFirstRange = true;
}

int FractalCreator::getRange(int iterations) const
{
    int range = 0;

    for (int i = 1; i < ranges.size(); ++i) {

        range = i;

        if (ranges[i] > iterations) {
            break;
        }
    }

    --range;

    assert(range > -1);
    assert(range < ranges.size());

    return range;
}

void FractalCreator::calculateRangeTotals()
{
    int rangeIndex = 0;

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
        int pixels = histogram[i];

        if (i >= ranges[rangeIndex + 1]) {
            ++rangeIndex;
        }
        rangeTotals[rangeIndex] += pixels;
    }
}

void FractalCreator::calculateTotalIterations()
{
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i) {
        total += histogram[i];
    }
}

void FractalCreator::calculateIteration()
{
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {

            std::pair<double, double> coords = zoomList.doZoom(x, y);

            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            fractal[y * m_width + x] = iterations;

            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                ++histogram[iterations];
            }
        }
    }
}

void FractalCreator::drawFractal()
{
    RGB startColor(0, 0, 0);
    RGB endColor(0, 0, 255);
    RGB colorDiff = endColor - startColor;

    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {

            int iterations = fractal[y * m_width + x];

            int range = getRange(iterations);
            int rangeTotal = rangeTotals[range];
            int rangeStart = ranges[range];

            std::uint8_t red = 0;
            std::uint8_t green = 0;
            std::uint8_t blue = 0;

            if (iterations != Mandelbrot::MAX_ITERATIONS) {

                int totalPixes = 0;

                for (int i = rangeStart; i <= iterations; ++i) {
                    totalPixes += histogram[i];
                }

                red = startColor.r + colorDiff.r * (double)totalPixes / rangeTotal; // std::pow(colorDiff.r, hue); //  255*hue
                green = startColor.g + colorDiff.g * (double)totalPixes / rangeTotal;
                blue = startColor.b + colorDiff.b * (double)totalPixes / rangeTotal;
            }

            bitmap.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::writeBitmap(std::string name)
{
    bitmap.write(name);
}
