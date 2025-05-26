#include "../image/Image.h"
#include "Transformation.h"
#include "Rotate.h"

Rotate::Rotate(Direction direction)
{
    this->direction = direction;
}

void Rotate::apply(Image* image) const
{
    image->rotate(direction);
}

std::string Rotate::getName() const
{
    return (direction == Direction::Left) ? "rotate left" : "rotate right";
}

Transformation* Rotate::clone() const
{
    return new Rotate(*this);
}