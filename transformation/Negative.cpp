#include "../image/Image.h"
#include "Transformation.h"
#include "Negative.h"

void Negative::apply(Image* image) const
{
    image->negative();
}

std::string Negative::getName() const
{
    return "negative";
}

Transformation* Negative::clone() const
{
    return new Negative(*this);
}