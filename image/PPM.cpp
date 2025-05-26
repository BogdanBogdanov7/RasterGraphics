#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "PPM.h"
#include "Image.h"

PPM::PPM()
{
    this->type = Type::PPM;
}

PPM::PPM(const std::string& filename)
{
    load(filename);
}
PPM::PPM(const PPM& first, const PPM& second, const std::string& direction)
{
    if(first.width != second.width || first.height != second.height)
    {
        throw std::invalid_argument("Images must have the same sizes for a collage!");
    }

    this->maxColorValue = first.maxColorValue;
    this->type = first.type;

    if(direction == "horizontal")
    {
        width = first.width + second.width;
        height = first.height;
        pixels.resize(height, std::vector<Pixel>(width));

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
        pixels.resize(height, std::vector<Pixel>(width));

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
PPM::PPM(const PPM& other)
{
    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->maxColorValue = other.maxColorValue;
    this->pixels = other.pixels;
}

PPM& PPM::operator=(const PPM& other)
{
    if(this != &other)
    {
        this->name = other.name;
        this->width = other.width;
        this->height = other.height;
        this->maxColorValue = other.maxColorValue;
        this->pixels = other.pixels;
    }
    return *this;
}

void PPM::load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if(!file.is_open())
    {
        throw std::runtime_error("Can't open the file!");
    }

    std::string header;
    file >> header;
    if(header != "P6")
    {
        throw std::invalid_argument("Invalid PPM format!");
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

    file >> width >> height >> maxColorValue;
    file.get();

    pixels.resize(height, std::vector<Pixel>(width));

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            Pixel& p = pixels[y][x];
            file.read(reinterpret_cast<char*>(&p), sizeof(Pixel));
        }
    }

    file.close();
}

void PPM::save(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open())
    {
        throw std::runtime_error("Can't open the file!");
    }

    file << "P6" << std::endl;
    file << width << " " << height << std::endl;
    file << maxColorValue << std::endl;

    for(const auto& row : pixels)
    {
        for(const auto& pixel : row)
        {
            file.write(reinterpret_cast<const char*>(&pixel), sizeof(Pixel));
        }
    }
    file.close();
}

void PPM::grayscale()
{
    for(auto& row : pixels)
    {
        for(auto& p : row)
        {
            char gray = static_cast<char>(0.299 * p.red + 0.587 * p.green + 0.114 * p.blue);
            p.red = gray;
            p.green = gray;
            p.blue = gray;
        }
    }
}

void PPM::monochrome()
{
    for(auto& row : pixels)
    {
        for(auto& p : row)
        {
            char avg = static_cast<char>((p.red + p.green + p.blue) / 3);
            if(avg < 127.5) //черно
            {
                p.red = 0;
                p.green = 0;
                p.blue = 0;
            }
            else //бяло
            {
                p.red = 255;
                p.green = 255;
                p.blue = 255;
            }
        }
    }
}

void PPM::negative()
{
    for(auto& row : pixels)
    {
        for(auto& p : row)
        {
            p.red = maxColorValue - p.red;
            p.green = maxColorValue - p.green;
            p.blue = maxColorValue - p.blue;
        }
    }
}

void PPM::rotate(Direction direction)
{
    std::vector<std::vector<Pixel>> rotated;
    if(direction == Direction::Left)
    {
        rotated.resize(width, std::vector<Pixel>(height));
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
        rotated.resize(width, std::vector<Pixel>(height));
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

std::string PPM::getName() const
{
    return name;
}

Type PPM::getType() const
{
    return Type::PPM;
}

void PPM::setName(const std::string& newName)
{
    name = newName;
}

int PPM::getWidth() const
{
    return width;
}

int PPM::getHeight() const
{
    return height;
}

Image* PPM::clone() const
{
    return new PPM(*this);
}