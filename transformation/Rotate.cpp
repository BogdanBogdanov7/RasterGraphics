#include "../image/Image.h"
#include "Transformation.h"
#include "Rotate.h"

void Rotate::apply(Image* image) const
{
    image->rotate(direction);
}

Transformation* Rotate::clone() const
{
    return new Rotate(*this);
}