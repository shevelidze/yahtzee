#ifndef DICE_H
#define DICE_H

#include <vector>
#include "Random.hpp"

class Dice
{
private:
    Random random;
    unsigned int lastRoll;

public:
    Dice();
    unsigned roll();
    unsigned getLastRoll();
};

#endif