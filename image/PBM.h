#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Image.h"

class PBM : public Image
{
private:
    int width, height;
    std::vector<std::vector<bool>> pixels; //1 е за черно, 0 е за бяло
public:
    PBM();
    PBM(const std::string& filename);
    PBM(const PBM& first, const PBM& second, const std::string& direction);
    PBM(const PBM& other);
    PBM& operator=(const PBM& other);

    void load(const std::string& filename) override;
    void save(const std::string& filename) const override;
    
    void grayscale() override; //няма ефект, защото е само черно и бяло
    void monochrome() override; //няма ефект, защото е само черно и бяло
    void negative() override;
    void rotate(Direction direction) override;

    std::string getName() const override;
    Type getType() const override;

    void setName(const std::string& newName) override;

    int getWidth() const override;
    int getHeight() const override;

    Image* clone() const override;

    ~PBM() override = default;
};