#ifndef DICEASCIIART_HPP
#define DICEASCIIART_HPP

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class DiceASCIIArt
{
  private:
    std::vector<std::vector<std::string>> lines;
    unsigned int diceLinesCount = UINT_MAX;

  public:
    DiceASCIIArt();
    std::string generate(std::vector<unsigned int> numbers);
};
#endif // DICEASCIIART_HPP
