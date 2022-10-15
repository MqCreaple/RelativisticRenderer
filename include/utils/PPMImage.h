#pragma once

#include "macro.h"
#include "utils/Color.h"
#include <string>
#include <iostream>
#include <fstream>

using std::string;

namespace gmq {

class PPMImage {
public:
    PPMImage(const string &fileName, Int width, Int height);
    void nextPixel(const Color &color);
private:
    std::ofstream fileStream;
};

} // namespace gmq