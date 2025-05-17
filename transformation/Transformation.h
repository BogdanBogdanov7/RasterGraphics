#pragma once
#include "../image/Image.h"

class Transformation
{
public:
    virtual void apply(Image* image) const = 0;
    virtual Transformation* clone() const = 0;
    virtual ~Transformation() = default;
};