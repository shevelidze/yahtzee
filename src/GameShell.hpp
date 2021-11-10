#ifndef GAMESHELL_HPP
#define GAMESHELL_HPP

#include "BasicShellModes.hpp"
#include <vector>

class GameShell
{
  private:
    std::vector<Player> players;
    ShellMode *playerlistEditMode;
    ShellMode *upperSectionGameMode;
    ShellMode *currentMode;
    bool running = true;

  public:
    void chageMode(ShellMode *newMode);
    GameShell();
    void launchShell();
    ShellMode *const getUpperSectionGameMode();
    void stopShell();
};

#endif // GAMESHELL_HPP
