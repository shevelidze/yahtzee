#include "DiceASCIIArt.hpp"

DiceASCIIArt::DiceASCIIArt()
{
    std::ifstream diceIfstream("dice.txt");
    std::string line;
    bool eof = diceIfstream.eof();
    bool newDice = true;
    while (!eof)
    {
        std::getline(diceIfstream, line);
        eof = diceIfstream.eof();

        if (newDice)
        {
            std::vector<std::string> oneOfDice;
            this->lines.push_back(oneOfDice);
            newDice = false;
        }

        if (line.length() == 0)
        {
            newDice = true;
        }
        else
        {
            this->lines.back().push_back(line);
        }
    }

    for (auto line : this->lines)
    {
        this->diceLinesCount = std::min(this->diceLinesCount, (unsigned int)(line.size()));
    }
}

std::string DiceASCIIArt::generate(std::vector<unsigned int> numbers)
{
    for (auto &number : numbers)
    {
        number--;
        if (number >= this->lines.size())
        {
            number = 0;
        }
    }
    std::string result = "";
    for (int lineIndex = 0; lineIndex < this->diceLinesCount; lineIndex++)
    {
        for (auto &number : numbers)
        {
            result += this->lines[number][lineIndex] + "    ";
        }
        result += '\n';
    }
    return result;
}