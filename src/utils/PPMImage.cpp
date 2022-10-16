#include "utils/PPMImage.h"

namespace gmq {

PPMImage::PPMImage(const string &fileName, Int width, Int height): fileStream(fileName + ".ppm", std::ios::out) {
    // std::cout << fileStream.fail() << std::endl;
    fileStream << "P3" << std::endl << width << " " << height << std::endl << 255 << std::endl;
}

void PPMImage::nextPixel(const Color &color) {
    Color c = Color (
        (color.r > 1)? 1: (color.r < 0 || std::isnan(color.r))? 0: color.r,
        (color.g > 1)? 1: (color.g < 0 || std::isnan(color.g))? 0: color.g,
        (color.b > 1)? 1: (color.b < 0 || std::isnan(color.b))? 0: color.b
    );
    fileStream << (int) (c.r * 255.99) << " " << (int) (c.g * 255.99) << " " << (int) (c.b * 255.99) << std::endl;
}

} // namespace gmq