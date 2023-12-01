#pragma once

#include "macro.h"
#include "utils/Color.h"
#include <cmath>
#include <string>
#include <iostream>
#include <ios>
#include <iomanip>
#include <fstream>

using std::string;

namespace gmq {

class BMPImage {
public:
    BMPImage(const string &filename, size_t width, size_t height);
    void write();
    void setPixel(size_t x, size_t y, const Color &color);
    ~BMPImage();
private:
    size_t width;
    size_t height;
    unsigned char *data;
    std::ofstream fileStream;
};

} // namespace gmq