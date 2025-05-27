#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "session/SessionHandling.h"
#include "utils/Utils.h"

int main()
{
    SessionHandling sessionHandler;
    std::string input;

    while(true)
    {
        std::cout << "> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::vector<std::string> args;
        std::string word;

        while(iss >> word)
        {
            args.push_back(word);
        }

        if(args.empty())
        {
            continue;
        }

        const std::string& command = args[0];

        if(Utils::toLower(command) == "exit")
        {
            sessionHandler.exit();
            break;
        }
        else if(Utils::toLower(command) == "load")
        {
            sessionHandler.load({args.begin() + 1, args.end()});
        }
        else if(Utils::toLower(command) == "save")
        {
            sessionHandler.save();
        }
        else if(Utils::toLower(command) == "saveas")
        {
            if(args.size() < 2)
            {
                std::cout << "Few arguments written." << std::endl;
                std::cout << "Format: saveas <filename>" << std::endl;
            }
            else
            {
                sessionHandler.saveAs(args[1]);
            }
        }
        else if(Utils::toLower(command) == "undo")
        {
            sessionHandler.undo();
        }
        else if(Utils::toLower(command) == "session_info")
        {
            sessionHandler.sessionInfo();
        }
        else if(Utils::toLower(command) == "help")
        {
            sessionHandler.help();
        }
        else if(Utils::toLower(command) == "collage")
        {
            if(args.size() != 5)
            {
                std::cout << "Few arguments written." << std::endl;
                std::cout << "Format: collage <direction> <image1> <image2> <outimage>" << std::endl;
            }
            else
            {
                sessionHandler.collage(args[1], args[2], args[3], args[4]);
            }
        }
        else if(Utils::toLower(command) == "grayscale" || Utils::toLower(command) == "monochrome" || Utils::toLower(command) == "negative")
        {
            sessionHandler.addTransformation(command);
        }
        else if(Utils::toLower(command) == "rotate")
        {
            if(args.size() != 2 || (args[1] != "left" && args[1] != "right"))
            {
                std::cout << "Few arguments written or invalid direction." << std::endl;
                std::cout << "Format: rotate <left/right>" << std::endl;
            }
            else
            {
                sessionHandler.addTransformation("rotate", args[1]);
            }
        }
        else if(Utils::toLower(command) == "add")
        {
            if(args.size() != 2)
            {
                std::cout << "Few arguments written." << std::endl;
            }
            else
            {
                sessionHandler.addOtherImage(args[1]);
            }
        }
        else if(Utils::toLower(command) == "close")
        {
            sessionHandler.close();
        }
        else if(Utils::toLower(command) == "switch")
        {
            if(args.size() != 2)
            {
                std::cout << "Few arguments written." << std::endl;
            }
            else
            {
                sessionHandler.switchTo(std::stoi(args[1]));
            }
        }
        else
        {
            std::cout << "No such command found! Type 'help' for a list with available commands. =D" << std::endl;
        }
    }

    return 0;
}