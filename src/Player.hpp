#ifndef PLAYER_H
#define PLAYER_H

#include "Dice.hpp"
#include <string>


class Player
{
  private:
    std::string name;
    

  public:
    std::vector<Dice> dice;
    Player(const std::string &name);
    const std::string &getName() const;
};

#endif