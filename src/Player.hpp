#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Dice.hpp"

class Player
{
private:
    std::string name;

public:
    Dice dice;
    Player(const std::string &name);
    const std::string &getName() const;
};

#endif