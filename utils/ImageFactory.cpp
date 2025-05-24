#include <iostream>
#include <string>
#include "../image/PBM.h"
#include "../image/PGM.h"
#include "../image/PPM.h"
#include "ImageFactory.h"
#include "Utils.h"

Image* ImageFactory::createImage(const std::string& filename)
{
    std::string extension = Utils::toLower(filename);
    if(Utils::endsWith(extension, ".pbm"))
    {
        return new PBM;
    }

    if(Utils::endsWith(extension, ".pgm"))
    {
        return new PGM;
    }

    if(Utils::endsWith(extension, ".ppm"))
    {
        return new PPM;
    }

    throw std::runtime_error(filename + " file format is not supported!");
}