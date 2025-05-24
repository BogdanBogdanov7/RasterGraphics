#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "../image/Image.h"
#include "../transformation/Transformation.h"

class Session
{
private:
    int id;
    std::vector<Image*> image;
    std::vector<Transformation*> transformations;
public:
    Session(int id);

    void addImage(const Image* const image);
    void addTransformation(const Transformation* const transformation);
    void undo();
    void save();
    void saveAs(const std::string& name);

    void info() const;

    int getId() const;
    const std::vector<Image*>& getImage() const;

    ~Session();
};