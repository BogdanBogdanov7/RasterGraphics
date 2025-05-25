#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "PGM.h"

PGM::PGM()
{
    this->type = Type::PGM;
}

PGM::PGM(const std::string& filename)
{
    load(filename);
}

PGM::PGM(const PGM& first, const PGM& second, const std::string& direction)
{
    if(first.width != second.width || first.height != second.height)
    {
        throw std::invalid_argument("Images must have the same sizes for a collage!");
    }

    this->maxGrayValue = first.maxGrayValue;
    this->type = first.type;

    if(direction == "horizontal")
    {
        width = first.width + second.width;
        height = first.height;
        pixels.resize(height, std::vector<int>(width));

        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < first.width; x++)
            {
                pixels[y][x] = first.pixels[y][x];
            }
            for(int x = 0; x < second.width; x++)
            {
                pixels[y][x + first.width] = second.pixels[y][x];
            }
        }
    }
    else if(direction == "vertical")
    {
        width = first.width;
        height = first.height + second.height;
        pixels.resize(height, std::vector<int>(width));

        for(int y = 0; y < first.height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                pixels[y][x] = first.pixels[y][x];
            }
        }

        for(int y = 0; y < second.height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                pixels[y + first.height][x] = second.pixels[y][x];
            }
        }
    }
    else
    {
        throw std::invalid_argument("Direction must be horizontal or vertical!");
    }

    name = "collage.pgm"; //името ще се замести от Session.cpp
}

PGM::PGM(const PGM& other)
{
    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->maxGrayValue = other.maxGrayValue;
    this->pixels = other.pixels;
}

PGM& PGM::operator=(const PGM& other) 
{
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

    std::string header;
    file >> header;
    if(header != "P5")
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

    file.close();
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
    file.close();
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
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                rotated[width - x - 1][y] = pixels[y][x];
            }
        }
        std::swap(width, height);
    }
    else
    {
        rotated.resize(width, std::vector<int>(height));
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                rotated[x][height - y - 1] = pixels[y][x];
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

Type PGM::getType() const
{
    return Type::PGM;
}

void PGM::setName(const std::string& newName)
{
    name = newName;
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