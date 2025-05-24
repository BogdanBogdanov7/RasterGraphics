#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include "PBM.h"

PBM::PBM()
{
    this->type = Type::PBM;
}

PBM::PBM(const std::string& filename)
{
    load(filename);
}
PBM::PBM(const PBM& other)
{
    this->filename = other.filename;
    this->width = other.width;
    this->height = other.height;
    this->pixels = other.pixels;
}
PBM& PBM::operator=(const PBM& other)
{
    if(this != &other)
    {
        this->filename = other.filename;
        this->width = other.width;
        this->height = other.height;
        this->pixels = other.pixels;
    }
    return *this;
}

void PBM::load(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);

    if(!file.is_open())
    {
        throw std::runtime_error("Can't open the file!");
    }

    std::string header;
    file >> header;
    if(header != "P4")
    {
        throw std::runtime_error("Invalid PBM format!");
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

    file >> width >> height;
    file.get();

    int bytesForRow = (width + 7) / 8; //всеки байт е 8 пиксела

    for(int y = 0; y < height; y++)
    {
        std::vector<char> row(bytesForRow);
        file.read(reinterpret_cast<char*>(row.data()), bytesForRow);
        for(int x = 0; x < width; x++)
        {
            int indexByte = x / 8;
            int indexBit = 7 - (x % 8);
            pixels[y][x] = ((row[indexByte] >> indexBit) & 1) == 0; //обръщаме ги - 0 е черно, 1 е бяло
        }
    }

    file.close();
}

void PBM::save(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary);
    if(!file.is_open())
    {
        throw std::runtime_error("Can't open the file!");
    }

    file << "P4" << std::endl;
    file << width << " " << height << std::endl;

    int bytesForRow = (width + 7) / 8;
    for(int y = 0; y < height; y++)
    {
        std::vector<char> row(bytesForRow, 0);
        for(int x = 0; x < width; x++)
        {
            if(!pixels[y][x]) //белият пиксел е 1, черният е 0
            {
                continue;
            }
            int indexByte = x / 8;
            int indexBit = 7 - (x % 8);
            row[indexByte] |= (1 << indexBit);
        }
        file.write(reinterpret_cast<const char*>(row.data()), bytesForRow);
    }
    file.close();
}

void PBM::negative()
{
    for(auto& row : pixels)
    {
        for(auto& pixel : row)
        {
            pixel = !pixel; //обръща цветовете
        }
    }
}

void PBM::rotate(Direction direction)
{
    std::vector<std::vector<bool>> rotated;
    if(direction == Left)
    {
        rotated.assign(width, std::vector<bool>(height));
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                rotated[x][height - y - 1] = pixels[y][x];
            }
        }
        std::swap(width, height);
    }
    else
    {
        rotated.assign(width, std::vector<bool>(height));
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                rotated[width - x - 1][y] = pixels[y][x];
            }
        }
        std::swap(width, height);
    }
    pixels = std::move(rotated);
}

std::string PBM::getName() const
{
    return filename;
}

Type PBM::getType() 
{
    return Type::PBM;
}

int PBM::getWidth() const
{
    return width;
}

int PBM::getHeight() const
{
    return height;
}

Image* PBM::clone() const
{
    return new PBM(*this);
}