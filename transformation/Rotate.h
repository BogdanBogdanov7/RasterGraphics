#pragma once
#include "../image/Image.h"
#include "Transformation.h"

class Rotate : public Transformation
{
private:
    Direction direction;
public:
    Rotate(Direction direction){}
    std::string getName() const override;
    void apply(Image* image) const override;
    Transformation* clone() const override;
    ~Rotate() override = default;
};