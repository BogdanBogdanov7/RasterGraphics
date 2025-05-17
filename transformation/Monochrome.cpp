#pragma once
#include "../image/Image.h"
#include "Transformation.h"
#include "Monochrome.h"

void Monochrome::apply(Image* image) const
{
    image->monochrome();
}

Transformation* Monochrome::clone() const
{
    return new Monochrome(*this);
}