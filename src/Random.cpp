#include "Random.hpp"

Fibanachi lastFibanachi;

Random::Random(unsigned int maxValue) : maxValue(maxValue), fibanachi(lastFibanachi)
{
    lastFibanachi.getNext();
}

unsigned int Random::getNext()
{
    return this->fibanachi.getNext() % this->maxValue + 1;
}