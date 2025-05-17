#pragma once
#include "Transformation.h"

class Grayscale : public Transformation
{
public:
    void apply(Image* image) const override;
    Transformation* clone() const override;
    ~Grayscale() override = default;
};