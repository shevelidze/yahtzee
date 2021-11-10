#include "GameShell.hpp"
#include "GameShellMode.hpp"
#include <fstream>
#include <iostream>
#include <string>

GameShell::GameShell()
{
    this->playerlistEditMode = new PlayerlistEditShellMode(this->players);
    this->upperSectionGameMode = new GameShellMode(this->players);
}

void GameShell::launchShell()
{
    std::ifstream helloIfstream("game_hello.txt");
    std::cout << helloIfstream.rdbuf() << "\n\n";
    this->chageMode(this->playerlistEditMode);

    std::string command;
    while (this->running)
    {
        std::cout << "~> ";
        std::getline(std::cin, command);
        if (command == "help")
            std::cout << this->currentMode->getHelpMessage() << '\n';
        else if (command == "exit")
            return;
        else
        {
            try
            {
                this->currentMode->processCommand(command, *this);
            }
            catch (int e)
            {
                std::cout << "Unknown command. Type \"help\" for help.\n";
            }
        }
    }
}

void GameShell::chageMode(ShellMode *newMode)
{
    this->currentMode = newMode;
    std::cout << this->currentMode->getHelpMessage() << '\n';
}

ShellMode *const GameShell::getUpperSectionGameMode()
{
    return this->upperSectionGameMode;
}

void GameShell::stopShell()
{
    this->running = false;
}