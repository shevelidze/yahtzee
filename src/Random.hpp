#ifndef RANDOM_H
#define RANDOM_H

#include "Fibanachi.hpp"

class Random
{
private:
    Fibanachi fibanachi;
    unsigned int maxValue;

public:
    unsigned int getNext();
    Random(unsigned int maxValue);
};

#endif