#include "Combinations.hpp"
#include <algorithm>

RepeatCombination::RepeatCombination(std::string name, unsigned repeatNumber, unsigned points)
    : name(name), repeatNumber(repeatNumber), points(points)
{
}

unsigned RepeatCombination::check(const std::vector<Dice> &dice) const
{
    std::vector<unsigned> repeatNumbers(6, 0);
    unsigned dicePointsSum = 0;
    for (auto oneDice : dice)
    {
        repeatNumbers[oneDice.getLastRoll()-1]++;
        dicePointsSum += oneDice.getLastRoll();
        if (repeatNumbers[oneDice.getLastRoll()-1] >= this->repeatNumber)
        {
            if (this->points == 0)
                return dicePointsSum;
            else
                return this->points;
        }
    }
    return 0;
}

std::string RepeatCombination::getName() const
{
    return this->name;
}

unsigned FullHouseCombination::check(const std::vector<Dice> &dice) const
{
    std::vector<unsigned> repeatNumbers(6, 0);
    for (auto oneDice : dice)
        repeatNumbers[oneDice.getLastRoll()-1]++;

    bool twoFound = false;
    bool threeFound = false;
    for (auto oneDice : dice)
    {
        if (repeatNumbers[oneDice.getLastRoll()-1] == 2)
            twoFound = true;
        if (repeatNumbers[oneDice.getLastRoll()-1] == 3)
            threeFound = true;

        if (twoFound && threeFound)
            return 25;
    }
    return 0;
}

std::string FullHouseCombination::getName() const
{
    return "Full House";
}

StraightCombination::StraightCombination(bool bigStraight) : isBigStraight(bigStraight)
{
}

std::string StraightCombination::getName() const
{
    if (this->isBigStraight)
        return "Big Straight";
    else
        return "Small Straight";
}

unsigned StraightCombination::check(const std::vector<Dice> &dice) const
{
    std::vector<Dice> sortedDice(dice);
    std::sort(sortedDice.begin(), sortedDice.end(),
              [](const Dice &a, const Dice &b) { return a.getLastRoll() < b.getLastRoll(); });
    bool firstWasWrong = false;
    for (auto diceIter = sortedDice.begin(); diceIter != sortedDice.end(); diceIter++)
    {
        if (diceIter != sortedDice.begin() && (diceIter - 1)->getLastRoll() - diceIter->getLastRoll() != 1)
        {
            if (diceIter - 1 == sortedDice.begin() && !this->isBigStraight)
                firstWasWrong = true;
            else if (!(diceIter + 1 == sortedDice.end() && !firstWasWrong && !this->isBigStraight))
                return 0;
        }
    }
    if (this->isBigStraight)
        return 40;
    else
        return 30;
}

unsigned ChanceCombination::check(const std::vector<Dice> &dice) const
{
    unsigned sum = 0;
    for (auto oneDice : dice)
        sum += oneDice.getLastRoll();
    return sum;
}

std::string ChanceCombination::getName() const
{
    return "Chance";
}

const std::vector<Combination *> lowerCombinations = {new RepeatCombination("3 of kind", 3, 0),
                                                      new RepeatCombination("4 of kind", 4, 0),
                                                      new FullHouseCombination(),
                                                      new StraightCombination(false),
                                                      new StraightCombination(true),
                                                      new RepeatCombination("YAHTZEE", 5, 50)};

UpperCombination::UpperCombination(std::string name, unsigned diceValue) : name(name), diceValue(diceValue)
{
}

std::string UpperCombination::getName() const
{
    return this->name;
}

unsigned UpperCombination::check(const std::vector<Dice> &dice) const
{
    unsigned sum = 0;
    for (auto oneDice : dice)
    {
        if (oneDice.getLastRoll() == this->diceValue)
            sum += this->diceValue;
    }
    return sum;
}

const std::vector<Combination *> upperCombinations = {
    new UpperCombination("Aces", 1),   new UpperCombination("Twos", 2),  new UpperCombination("Threes", 3),
    new UpperCombination("Fourth", 4), new UpperCombination("Fives", 5), new UpperCombination("Sixes", 6),
};