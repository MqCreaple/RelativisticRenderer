#include "utils/BMPImage.h"

namespace gmq {

BMPImage::BMPImage(const string &filename, size_t width, size_t height):
    width(width), height(height), fileStream(filename + ".bmp", std::ios::out | std::ios::binary), data(new unsigned char[width * height * 3]) {}

void BMPImage::write() {
    size_t fileSize = 54 + 3 * width * height;
    unsigned char fileHeader[14] = {
        'B', 'M',             // magic
        (unsigned char)(fileSize), (unsigned char)(fileSize >> 8), (unsigned char)(fileSize >> 16), (unsigned char)(fileSize >> 24), // size
        0, 0,                 // reserved
        0, 0,                 // reserved
        54, 0, 0, 0           // offset
    };
    unsigned char infoHeader[40] = {
        40, 0, 0, 0,          // info header size
        (unsigned char)(width), (unsigned char)(width >> 8), (unsigned char)(width >> 16), (unsigned char)(width >> 24), // width
        (unsigned char)(height), (unsigned char)(height >> 8), (unsigned char)(height >> 16), (unsigned char)(height >> 24), // height
        1, 0,                 // number color planes
        24, 0,                // bits per pixel
        0, 0, 0, 0,           // compression is none
        (unsigned char)(3 * width * height), (unsigned char)(3 * width * height >> 8), (unsigned char)(3 * width * height >> 16), (unsigned char)(3 * width * height >> 24), // image bits size
        0x13, 0x0B, 0, 0,     // horz resoluition in pixel / m
        0x13, 0x0B, 0, 0,     // vert resolutions (0x03C3 = 96 dpi, 0x0B13 = 72 dpi)
        0, 0, 0, 0,           // #colors in pallete
        0, 0, 0, 0,           // #important colors
    };
    fileStream.write((char *)fileHeader, 14);
    fileStream.write((char *)infoHeader, 40);
    fileStream.write((char *)data, 3 * width * height);
}

void BMPImage::setPixel(size_t x, size_t y, const Color &color) {
    size_t index = 3 * (y * width + x);
    data[index + 0] = (unsigned char)(std::min(static_cast<Float>(1.0), color.b) * 255);
    data[index + 1] = (unsigned char)(std::min(static_cast<Float>(1.0), color.g) * 255);
    data[index + 2] = (unsigned char)(std::min(static_cast<Float>(1.0), color.r) * 255);
}

std::ofstream &BMPImage::getOutputFStream() {
    return this->fileStream;
}

BMPImage::~BMPImage() {
    delete[] data;
}

} // namespace gmq