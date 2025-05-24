#include <iostream>
#include "SessionHandling.h"
#include "../utils/ImageFactory.h"

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