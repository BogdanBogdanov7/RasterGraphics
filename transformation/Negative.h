#pragma once
#include "../image/Image.h"
#include "Transformation.h"

class Negative : public Transformation
{
public:
    std::string getName() const override;
    void apply(Image* image) const override;
    Transformation* clone() const override;
    ~Negative() = default;
};