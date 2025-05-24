#pragma once
#include "../image/Image.h"
#include "Transformation.h"

class Monochrome : public Transformation
{
public:
    std::string getName() const override;
    void apply(Image* image) const override;
    Transformation* clone() const override;
    ~Monochrome() = default;
};