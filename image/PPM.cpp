#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include "PPM.h"
#include "Image.h"

PPM::PPM(const std::string& filename)
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
}

PPM::PPM(const PPM& other)
{
    this->width = other.width;
    this->height = other.height;
    this->maxColorValue = other.maxColorValue;\
    this->pixels = other.pixels;
}

PPM& PPM::operator=(const PPM& other)
{
    if(this != &other)
    {
        this->width = other.width;
        this->height = other.height;
        this->maxColorValue = other.maxColorValue;
        this->pixels = other.pixels;
    }
    return *this;
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

Type PPM::getType()
{
    return Type::PPM;
}