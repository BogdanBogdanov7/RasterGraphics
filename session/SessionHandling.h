#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Session.h"

class SessionHandler
{
private:
    std::vector<Session*> sessions;
    int currentSessionId = -1;
    int nextSessionId = 1;
public:
    void load(const std::vector<std::string>& filenames);
    void add(const std::string& filename);
    void switchTo(int id);
    void applyGrayscale();
    void applyMonochrome();
    void applyNegative();
    void rotate(Direction dir);
    void undo();
    void save();
    void saveAs(const std::string& name);
    void sessionInfo() const;

    ~SessionHandler();
};