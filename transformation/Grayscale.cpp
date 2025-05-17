#include "Transformation.h"
#include "Grayscale.h"

void Grayscale::apply(Image* image) const
{
    image->grayscale();
}

Transformation* Grayscale::clone() const
{
    return new Grayscale(*this);
}