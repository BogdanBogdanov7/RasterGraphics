#pragma once
#include "../image/Image.h"
#include "Transformation.h"

class Monochrome : public Transformation
{
public:
    void apply(Image* image) const override;
    Transformation* clone() const override;
    ~Monochrome() = default;
};