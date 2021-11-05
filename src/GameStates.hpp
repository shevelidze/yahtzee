#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <string>
#include <vector>
#include <iostream>
#include "Player.hpp"

class GameState
{
public:
    virtual std::string getHelpMessage() = 0;
    virtual void processCommand(std::string command) = 0;
};

class PlayerlistEdit : public GameState
{
private:
    std::vector<Player> &players;

public:
    PlayerlistEdit(std::vector<Player> &players);
    std::string getHelpMessage() override final;
    void processCommand(std::string command) override final;
    void addPlayer(std::string playerName);
    void deletePlayer(size_t playerIndex);
};

#endif