#include <iostream>
#include <vector>
#include "../image/Image.h"
#include "Session.h"
#include "../transformation/Transformation.h"
#include "../image/PBM.h"
#include "../image/PGM.h"
#include "../image/PPM.h"

Session::Session(int id)
{
    this->id = id;
}

void Session::addImage(const Image* const someImage)
{
    image.push_back(someImage->clone());
}

void Session::addTransformation(const Transformation* const transformation)
{
    transformations.push_back(transformation->clone());
}

void Session::undo() //!!!toDO!!!
{
    if(transformations.empty())
    {
        std::cout << "No transformations have been made!" << std::endl;
        return;
    }

    delete transformations.back();
    transformations.pop_back();

    std::cout << "The last transformation is undone!" << std::endl;
}

void Session::save()
{
    for(Image* img : image)
    {
        Image* changedImage = img->clone();
        for(Transformation* t : transformations)
        {
            t->apply(changedImage);
        }
        changedImage->save(img->getName());
        delete changedImage;
    }
    transformations.clear();
}

void Session::saveAs(const std::string& name)
{
    if(!image.empty())
    {
        Image* changedImage = image[0]->clone();
        for(Transformation* transformation : transformations)
        {
            transformation->apply(changedImage);
        }
        changedImage->save(name);
        delete changedImage;
    }
    transformations.clear();
}

void Session::collage(const std::string& direction, const std::string& firstImageName, const std::string& secondImageName, const std::string& resultImageName)
{
    Image* firstImage = nullptr;
    Image* secondImage = nullptr;

    for(Image* img : image)
    {
        if(img->getName() == firstImageName)
        {
            firstImage = img;
        }
        if(img->getName() == secondImageName)
        {
            secondImage = img;
        }
    }

    if(!firstImage || !secondImage) //проверява дали не са nullptr
    {
        std::cerr << "Cannot find valid image!" << std::endl;
        return;
    }

    if(firstImage->getType() != secondImage->getType())
    {
        std::cerr << "Images must be in the same file format!" << std::endl;
        return;
    }

    if(firstImage->getHeight() != secondImage->getHeight() || firstImage->getWidth() != secondImage->getWidth())
    {
        std::cerr << "Images must be the same size!" << std::endl;
        return;
    }

    Image* firstImageCopy = firstImage->clone();
    Image* secondImageCopy = secondImage->clone();

    for(Transformation* transformation : transformations)
    {
        transformation->apply(firstImageCopy);
        transformation->apply(secondImageCopy);
    }

    Image* collageImage = nullptr;

    if(firstImage->getType() == Type::PBM)
    {
        collageImage = new PBM(*dynamic_cast<PBM*>(firstImageCopy), *dynamic_cast<PBM*>(secondImageCopy), direction);
    }
    if(firstImage->getType() == Type::PGM)
    {
        collageImage = new PGM(*dynamic_cast<PGM*>(firstImageCopy), *dynamic_cast<PGM*>(secondImageCopy), direction);
    }
    if(firstImage->getType() == Type::PPM)
    {
        collageImage = new PPM(*dynamic_cast<PPM*>(firstImageCopy), *dynamic_cast<PPM*>(secondImageCopy), direction);
    }

    if(!collageImage)
    {
        std::cerr << "Cannot create a collage!" << std::endl;
        delete firstImageCopy;
        delete secondImageCopy;
        return;
    }

    collageImage->setName(resultImageName);
    image.push_back(collageImage);

    delete firstImageCopy;
    delete secondImageCopy;

    std::cout << "New collage " << resultImageName << " created" << std::endl;
}

void Session::info() const
{
    std::cout << "Session ID: " << id << std::endl;
    
    if(!image.empty())
    {
        std::cout << "Name of images in the session: ";
        for(const Image* img : image)
        {
            std::cout << img->getName() << " ";
        }
    }
    else
    {
        std::cout << "no images found!" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Pending transformations: ";
    if(!transformations.empty())
    {
        for(const Transformation* transformation : transformations)
        {
            std::cout << transformation->getName() << " ";
        }
    }
    else
    {
        std::cout << "no transformations found!" << std::endl;
    }
    std::cout << std::endl;
}

int Session::getId() const
{
    return id;
}

Session::~Session()
{
    for(Image* images : image)
    {
        delete images;
    }
    image.clear();

    for(Transformation* transformation : transformations)
    {
        delete transformation;
    }
    transformations.clear();
}