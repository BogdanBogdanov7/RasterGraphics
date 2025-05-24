#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

class PBM : public Image
{
private:
    std::string filename;
    int width;
    int height;
    std::vector<std::vector<bool>> pixels; //true е за черно, false е за бяло
public:
    PBM();
    PBM(const std::string& filename);
    PBM(const PBM& other);
    PBM& operator=(const PBM& other);

    void load(const std::string& filename) override;
    void save(const std::string& filename) const override;
    
    void grayscale() override; //няма ефект, защото е само черно и бяло
    void monochrome() override; //няма ефект, защото е само черно и бяло
    void negative() override;
    void rotate(Direction direction) override;

    std::string getName() const override;
    Type getType() override;

    int getWidth() const override;
    int getHeight() const override;

    Image* clone() const override;

    ~PBM() override = default;
};