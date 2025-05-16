#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class Type {PBM, PGM, PPM};
enum Direction {Left, Right};

class Image
{
public:
    virtual void load(const std::string& filename) = 0;
    virtual void save(const std::string& filename) const = 0;

    virtual void grayscale() = 0;
    virtual void monochrome() = 0;
    virtual void negative() = 0;
    virtual void rotate(Direction direction) = 0;

    virtual std::string getName() const = 0;
    virtual Type getType() = 0;
    
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual Image* clone() const = 0;

    virtual ~Image() = default;
};