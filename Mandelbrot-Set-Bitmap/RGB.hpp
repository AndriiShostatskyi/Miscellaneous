#pragma once

struct RGB {
    double r;
    double g;
    double b;

    RGB(double r, double g, double b)
        : r{ r }
        , g{ g }
        , b{ b }
    {
    }
};

inline RGB operator-(const RGB& first, const RGB& second)
{
    return RGB(first.r - second.r, first.g - second.g, first.b - second.b);
}
