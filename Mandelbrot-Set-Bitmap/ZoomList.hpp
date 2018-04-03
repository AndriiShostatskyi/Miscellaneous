#pragma once

#include <vector>
#include <utility>

struct Zoom {
    int x{ 0 };
    int y{ 0 };

    double scale{ 0.0 };

    Zoom(int x, int y, double scale)
        : x{ x }
        , y{ y }
        , scale{ scale }
    {
    }
};

class ZoomList {
    double m_xCenter{ 0 };
    double m_yCenter{ 0 };
    double m_scale{ 1.0 };

    int m_width{ 0 };
    int m_height{ 0 };

    std::vector<Zoom> zooms;

public:
    ZoomList(int width, int height);
    void add(const Zoom& zoom);
    std::pair<double, double> doZoom(int x, int y);
};
