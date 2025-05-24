#pragma once
#include "Transformation.h"

class Grayscale : public Transformation
{
public:
    std::string getName() const override;
    void apply(Image* image) const override;
    Transformation* clone() const override;
    ~Grayscale() override = default;
};