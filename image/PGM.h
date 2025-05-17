#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

class PGM : public Image
{
private:
    std::string name;
    int width;
    int height;
    int maxGrayValue;
    std::vector<std::vector<int>> pixels;

public:
    PGM(const std::string& filename);
    PGM(const PGM& other);
    PGM& operator=(const PGM& other);
    
    void load(const std::string& filename) override;
    void save(const std::string& filename) const override;
    
    void grayscale() override;
    void monochrome() override;
    void negative() override;
    void rotate(Direction direction) override;
    
    std::string getName() const override;
    Type getType() override;
    int getWidth() const override;
    int getHeight() const override;
    
    Image* clone() const override;
    
    ~PGM() override = default;
};