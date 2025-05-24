#pragma once
#include <string>
#include "../image/PBM.h"
#include "../image/PGM.h"
#include "../image/PPM.h"
#include "Utils.h"

class ImageFactory : Utils
{
public:
    static Image* createImage(const std::string& filename);
};