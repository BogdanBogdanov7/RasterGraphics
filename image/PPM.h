#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

struct Pixel
{
    char red, green, blue;
};

class PPM : public Image
{
private:
    int width, height;
    int maxColorValue;
    std::vector<std::vector<Pixel>> pixels;

public:
    PPM(const std::string& filename);
    PPM(const PPM& other);
    PPM& operator=(const PPM& other);

    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotate(Direction direction) override;
    void save(const std::string& filename) const override;
    Image* clone() const override;

    std::string getName() const override;
    Type getType() override;

    ~PPM() override;
};