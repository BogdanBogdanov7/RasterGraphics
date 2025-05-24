#include "Transformation.h"
#include "Grayscale.h"

void Grayscale::apply(Image* image) const
{
    image->grayscale();
}

std::string Grayscale::getName() const
{
    return "grayscale";
}

Transformation* Grayscale::clone() const
{
    return new Grayscale(*this);
}