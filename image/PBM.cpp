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
PBM::PBM(const PBM& first, const PBM& second, const std::string& direction)
{
    if(first.width != second.width || first.height != second.height)
    {
        throw std::invalid_argument("Images must have the same sizes for a collage!");
    }

    this->type = Type::PBM;

    if(direction == "horizontal")
    {
        width = first.width + second.width;
        height = first.height;
        pixels.resize(height, std::vector<bool>(width));

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
        pixels.resize(height, std::vector<bool>(width));

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
PBM::PBM(const PBM& other)
{
    this->name = other.name;
    this->width = other.width;
    this->height = other.height;
    this->pixels = other.pixels;
}
PBM& PBM::operator=(const PBM& other)
{
    if(this != &other)
    {
        this->name = other.name;
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

    //пропускане на коментари и празни редове преди ширината и височината
    while (true) 
    {
        char c = file.peek();
        if(c == '#') 
        {
            std::string commentLine;
            std::getline(file, commentLine);
        } 
        else if(isspace(c))
        {
            file.get();  // пропуска празни места и нови редове
        } 
        else 
        {
            break;
        }
    }

    file >> width >> height;
    file.get();

    pixels.resize(height, std::vector<bool>(width));

    int bytesForRow = (width + 7) / 8; //всеки байт е 8 пиксела

    for(int y = 0; y < height; y++)
    {
        std::vector<unsigned char> row(bytesForRow);
        file.read(reinterpret_cast<char*>(row.data()), bytesForRow);
        for(int x = 0; x < width; x++)
        {
            int indexByte = x / 8;
            int indexBit = 7 - (x % 8);
            pixels[y][x] = ((row[indexByte] >> indexBit) & 1) != 0; //обръщаме ги - 0 е черно, 1 е бяло
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
        std::vector<unsigned char> row(bytesForRow, 0);
        for(int x = 0; x < width; x++)
        {
            if(pixels[y][x]) //ако пикселът е 1 (т.е бял)
            {
                int indexByte = x / 8;
                int indexBit = 7 - (x % 8);
                row[indexByte] |= (1 << indexBit);
            }
            
        }
        file.write(reinterpret_cast<const char*>(row.data()), bytesForRow);
    }
    file.close();
}

void PBM::grayscale()
{
    //няма ефект, защото е само черно и бяло
} 
void PBM::monochrome() 
{
    //няма ефект, защото е само черно и бяло
}

void PBM::negative()
{
    for(auto& row : pixels)
    {
        for(std::vector<bool>::reference pixel : row)
        {
            pixel = !pixel;
        }
    }
    //std::cout << "width = " << width << ", height = " << height << std::endl;
}

void PBM::rotate(Direction direction)
{
    std::vector<std::vector<bool>> rotated;
    if(direction == Direction::Left)
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
    return name;
}

Type PBM::getType() const
{
    return Type::PBM;
}

void PBM::setName(const std::string& newName)
{
    name = newName;
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