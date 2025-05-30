#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

class PGM : public Image
{
private:
    int width, height;
    int maxGrayValue;
    std::vector<std::vector<int>> pixels;

public:
    PGM();
    PGM(const std::string& filename);
    PGM(const PGM& first, const PGM& second, const std::string& direction);
    PGM(const PGM& other);
    PGM& operator=(const PGM& other);
    
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
    
    ~PGM() override = default;
};