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
    /**
     * @brief Construct a new BMPImage object.
     * Create a BMP image writer with the file name (without the '.bmp' file extension), the
     * width, and the height of the image.
     * @param filename Image file name (without file extension)
     * @param width Image width
     * @param height Image height
     */
    BMPImage(const string &filename, size_t width, size_t height);
    void write();
    void setPixel(size_t x, size_t y, const Color &color);
    std::ofstream &getOutputFStream();
    ~BMPImage();
private:
    size_t width;
    size_t height;
    unsigned char *data;
    std::ofstream fileStream;
};

} // namespace gmq