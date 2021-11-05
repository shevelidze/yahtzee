#ifndef GAMESHELL_H
#define GAMESHELL_H

#include "GameStates.hpp"
#include <vector>

class GameShell
{
private:
    std::vector<Player> players;
    GameState* playerlistEditState;
    GameState* currentState;
    void chageState(GameState* newState);

public:
    GameShell();
    void launchShell();
};

#endif