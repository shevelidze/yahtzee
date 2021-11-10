#ifndef COMBINATIONS_HPP
#define COMBINATIONS_HPP

#include "Dice.hpp"
#include <string>
#include <vector>

class Combination
{
  public:
    virtual unsigned check(const std::vector<Dice> &dice) const = 0;
    virtual std::string getName() const = 0;
};

class RepeatCombination : public Combination
{
  private:
    std::string name;
    unsigned repeatNumber;
    unsigned points;

  public:
    RepeatCombination(std::string name, unsigned repeatNumber, unsigned points);
    unsigned check(const std::vector<Dice> &dice) const override final;
    std::string getName() const override final;
};

class FullHouseCombination : public Combination
{
  public:
    unsigned check(const std::vector<Dice> &dice) const override final;
    std::string getName() const override final;
};

class StraightCombination : public Combination
{
  private:
    bool isBigStraight;

  public:
    StraightCombination(bool bigStraight);
    unsigned check(const std::vector<Dice> &dice) const override final;
    std::string getName() const override final;
};

class ChanceCombination : public Combination
{
  public:
    unsigned check(const std::vector<Dice> &dice) const;
    std::string getName() const;
};

extern const std::vector<Combination *> lowerCombinations;

class UpperCombination : public Combination
{
  private:
    unsigned diceValue;
    std::string name;
  public:
    UpperCombination(std::string name, unsigned diceValue);
    unsigned check(const std::vector<Dice> &dice) const;
    std::string getName() const;
};

extern const std::vector<Combination *> upperCombinations;

#endif // COMBINATIONS_HPP
