#include "Dice.hpp"

Dice::Dice() : random(6){};

unsigned int Dice::roll()
{
    this->lastRoll = this->random.getNext();
    return lastRoll;
}

unsigned Dice::getLastRoll()
{
    return this->lastRoll;
}
