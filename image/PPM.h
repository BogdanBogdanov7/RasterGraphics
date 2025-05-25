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
    std::string name;
    int width, height;
    int maxColorValue;
    std::vector<std::vector<Pixel>> pixels;

public:
    PPM();
    PPM(const std::string& filename);
    PPM::PPM(const PPM& first, const PPM& second, const std::string& direction);
    PPM(const PPM& other);
    PPM& operator=(const PPM& other);

    void load(const std::string& filename) override;
    void save(const std::string& filename) const override;

    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotate(Direction direction) override;
    
    std::string getName() const override;
    Type getType() const override;

    void setName(const std::string& newName) override;
    
    int getWidth() const override;
    int getHeight() const override;
    Image* clone() const override;

    ~PPM() override = default;
};