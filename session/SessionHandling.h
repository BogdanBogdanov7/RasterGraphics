#pragma once
#include <vector>
#include <iostream>
#include "Session.h"

class SessionHandling
{
private:
    std::vector<Session*> sessions;
    int currentSessionId = -1;
    int nextSessionId = 1;
public:
    void load(const std::vector<std::string>& filenames);
    void add(const std::string& filename);
    void save();
    void saveAs(const std::string& name);
    void undo();
    void sessionInfo() const;
    void help();
    void exit();
    void addTransformation(const std::string& tName);
    void addTransformation(const std::string& tName, const std::string& direction);
    void collage(const std::string& direction, const std::string& firstImageName, const std::string& secondImageName, const std::string& resultImageName);
    void switchTo(int id);
    void rotate(Direction dir);
    Session* getCurrentSession() const;

    ~SessionHandling();
};