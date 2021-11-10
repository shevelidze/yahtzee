#ifndef BASICSHELLMODES_HPP
#define BASICSHELLMODES_HPP

#include "Player.hpp"
#include <iostream>
#include <string>
#include <vector>


class GameShell;

class ShellMode
{
  public:
    virtual std::string getHelpMessage() = 0;
    virtual void processCommand(std::string command, GameShell &shell) = 0;
};

class PlayerlistEditShellMode : public ShellMode
{
  private:
    std::vector<Player> &players;

  public:
    PlayerlistEditShellMode(std::vector<Player> &players);
    std::string getHelpMessage() override final;
    void processCommand(std::string command, GameShell &shell) override final;
    void addPlayer(std::string playerName);
    void deletePlayer(size_t playerIndex);
};

#endif // BASICSHELLMODES_HPP
