#ifndef DICE_HPP
#define DICE_HPP

#include "Random.hpp"
#include <vector>


class Dice
{
  private:
    Random random;
    unsigned int lastRoll;

  public:
    Dice();
    unsigned roll();
    unsigned getLastRoll() const;
};

#endif // DICE_HPP
