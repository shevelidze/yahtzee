#ifndef DICEASCIIART_H
#define DICEASCIIART_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

class DiceASCIIArt
{
private:
	std::vector<std::vector<std::string>> lines;
	unsigned int diceLinesCount = UINT_MAX;

public:
	DiceASCIIArt();
	std::string generate(std::vector<unsigned int> numbers);
};
#endif