#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "PGM.h"

PGM::PGM(const std::string& filename)
{
    load(filename);
}

PGM::PGM(const PGM& other)
{
    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->maxGrayValue = other.maxGrayValue;
    this->pixels = other.pixels;
}

PGM& PGM::operator=(const PGM& other) { //енъма и хедъра са с едно и също име -> трябва или да се промени името,
                                        //или да намеря как да разбере, че не се има предвид enum, а обекта
    if(this != &other)
    {
        this->name = other.name;
        this->width = other.width;
        this->height = other.height;
        this->maxGrayValue = other.maxGrayValue;
        this->pixels = other.pixels;
    }
    return *this;
}

void PGM::load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if(!file.is_open())
    {
        throw std::runtime_error("Can't open the file!");
    }

    std::string format;
    file >> format;
    if(format != "P5")
    {
        throw std::runtime_error("Invalid PGM format!");
    }

    //пропускане на коментари
    char ch;
    file.get(ch);
    while(ch == '#')
    {
        while(file.get(ch) && ch != '\n')
        {
            file.get(ch);
        }
    }
    file.unget();

    file >> width >> height >> maxGrayValue;
    file.get();

    if(maxGrayValue > 255)
    {
        throw std::runtime_error("maxGrayValue is only supported under 255");
    }

    pixels.resize(height, std::vector<int>(width));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixels[i][j] = static_cast<char>(file.get());
        }
    }
    name = filename;
}

void PGM::save(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open())
    {
        throw std::runtime_error("Can't open the file!");
    }

    file << "P5" << std::endl;
    file << width << " " << height << std::endl;
    file << maxGrayValue << std::endl;

    for(const auto& row : pixels)
    {
        for(int pixel : row)
        {
            file.put(static_cast<char>(pixel));
        }
    }
}

void PGM::grayscale() {} //вече е grayscale

void PGM::monochrome()
{
    for(auto& row : pixels)
    {
        for(int& pixel : row)
        {
            pixel = pixel > (maxGrayValue / 2) ? maxGrayValue : 0;
        }
    }
}

void PGM::negative()
{
    for(auto& row : pixels)
    {
        for(int& pixel : row)
        {
            pixel = maxGrayValue - pixel;
        }
    }
}

void PGM::rotate(Direction direction)
{
    std::vector<std::vector<int>> rotated;
    if(direction == Left)
    {
        rotated.resize(width, std::vector<int>(height));
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                rotated[width - j - 1][i] = pixels[i][j];
            }
        }
        std::swap(width, height);
    }
    else
    {
        rotated.resize(width, std::vector<int>(height));
        for(int i = 0; i < height; i++)
        {
            for(int j = 0; j < width; j++)
            {
                rotated[j][height - i - 1] = pixels[i][j];
            }
        }
        std::swap(width, height);
    }
    pixels = std::move(rotated);
}

std::string PGM::getName() const
{
    return name;
}

Type PGM::getType()
{
    return Type::PGM;
}

int PGM::getWidth() const
{
    return width;
}

int PGM::getHeight() const
{
    return height;
}

Image* PGM::clone() const
{
    return new PGM(*this);
}