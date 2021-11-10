#include "Dice.hpp"

Dice::Dice() : random(6){
    this->lastRoll = this->random.getNext();
};

unsigned int Dice::roll()
{
    this->lastRoll = this->random.getNext();
    return lastRoll;
}

unsigned Dice::getLastRoll() const
{
    return this->lastRoll;
}
