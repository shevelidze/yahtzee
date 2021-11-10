#include "Player.hpp"

Player::Player(const std::string &name) : name(name), dice(5)
{
}

const std::string &Player::getName() const
{
    return this->name;
}