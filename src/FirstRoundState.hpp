#ifndef FIRSTROUNDSTATE_H
#define FIRSTROUNDSTATE_H

#include "GameStates.hpp"
#include <string>

class FirstRoundState : public GameState
{
public:
    std::string getHelpMessage();
    void processCommand(std::string command);
};

#endif