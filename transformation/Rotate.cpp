#include "../image/Image.h"
#include "Transformation.h"
#include "Rotate.h"

void Rotate::apply(Image* image) const
{
    image->rotate(direction);
}

std::string Rotate::getName() const
{
    return (direction == Left) ? "rotate left" : "rotate right";
}

Transformation* Rotate::clone() const
{
    return new Rotate(*this);
}