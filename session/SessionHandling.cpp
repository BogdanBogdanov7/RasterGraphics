#include <iostream>
#include "SessionHandling.h"
#include "../utils/ImageFactory.h"
#include "../image/PBM.h"
#include "../image/PGM.h"
#include "../image/PPM.h"

void SessionHandling::load(const std::vector<std::string>& filenames)
{
    Session* newSession = new Session(nextSessionId);
    nextSessionId++;

    for(const std::string& file : filenames)
    {
        try
        {
            Image* img = ImageFactory::createImage(file);
            img->load(file);
            newSession->addImage(img);
            std::cout << "Image \"" << file << "\" added" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error loading file \"" << file << "\": " << e.what() << std::endl;
        }
        
    }

    sessions.push_back(newSession);
    currentSessionId = newSession->getId();
    std::cout << "Session with ID: " << currentSessionId << " started" << std::endl;
}

Session* SessionHandling::getCurrentSession() const
{
    for(Session* s : sessions)
    {
        if(s->getId() == currentSessionId)
        {
            return s;
        }
    }
    return nullptr;
}

void SessionHandling::collage(const std::string& direction, const std::string& firstImageName, const std::string& secondImageName, const std::string& resultImageName)
{
    Session* current = getCurrentSession();

    if(!current)
    {
        std::cout << "No sessions are active!" << std::endl;
        return;
    }

    const auto& images = current->getImage();
    const Image* firstImage = nullptr;
    const Image* secondImage = nullptr;

    for(Image* img : images)
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

    Image* res = nullptr;

    if(firstImage->getType() == Type::PBM)
    {
        res = new PBM(*dynamic_cast<const PBM*>(firstImage), *dynamic_cast<const PBM*>(secondImage), direction);
    }
    if(firstImage->getType() == Type::PGM)
    {
        res = new PGM(*dynamic_cast<const PGM*>(firstImage), *dynamic_cast<const PGM*>(secondImage), direction);
    }
    if(firstImage->getType() == Type::PPM)
    {
        res = new PPM(*dynamic_cast<const PPM*>(firstImage), *dynamic_cast<const PPM*>(secondImage), direction);
    }
    else
    {
        std::cout << "This file format is not supported!" << std::endl;
        return;
    }

    res->setName(resultImageName);
    current->addImage(res);

    std::cout << "New collage \"" << resultImageName << "\" created" << std::endl;
}

void SessionHandling::help()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << " load <file1> <file2> ...     - Loads one or more images into a new session." << std::endl;
    std::cout << " save                         - Applies all transformations and saves all new images." << std::endl;
    std::cout << " saveas <name>                - Saves the first loaded image with a new name." << std::endl;
    std::cout << " undo                         - Undoes the last applied transformation to the image." << std::endl;
    std::cout << " add <transformation>         - Adds a transformation to the image." << std::endl;
    std::cout << " session info                 - Displays information about the current session." << std::endl;
    std::cout << " session switch <id>          - Switches to a different session, with the id you've provided." << std::endl;
    std::cout << " help                         - Displays this help message." << std::endl;
    std::cout << " exit                         - Exits the program." << std::endl;
}

void SessionHandling::exit()
{
    for(Session* s : sessions)
    {
        delete s;
    }
    sessions.clear();

    std::cout << "Exiting the program. All sessions are deleted." << std::endl;
}

SessionHandling::~SessionHandling()
{
    for(Session* s : sessions)
    {
        delete s;
    }
    sessions.clear();
}