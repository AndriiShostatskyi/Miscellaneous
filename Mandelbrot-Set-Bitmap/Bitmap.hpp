#pragma once

#include <string>
#include <cstdint>
#include <memory>

class Bitmap {
    int m_width{ 0 };
    int m_height{ 0 };

    std::unique_ptr<uint8_t[]> m_pPixel{ nullptr };

public:
    Bitmap(int width, int height);
    bool write(const std::string& fileName);
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
};
