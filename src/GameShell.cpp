#include "GameShell.hpp"
#include <iostream>
#include <string>
#include <fstream>

GameShell::GameShell()
{
    this->playerlistEditState = new PlayerlistEdit(this->players);
}

void GameShell::launchShell()
{
    std::ifstream helloIfstream("game_hello.txt");
    std::cout << helloIfstream.rdbuf() << "\n\n";
    this->chageState(this->playerlistEditState);

    std::string command;
    while (true)
    {
        std::cout << "~> ";
        std::getline(std::cin, command);
        if (command == "help") std::cout << this->currentState->getHelpMessage() << '\n';
        else if (command == "exit") return;
        else this->currentState->processCommand(command);
    }
}

void GameShell::chageState(GameState *newState)
{
    this->currentState = newState;
    std::cout << this->currentState->getHelpMessage() << '\n';
}