#include "GameStates.hpp"

PlayerlistEdit::PlayerlistEdit(std::vector<Player> &players) : players(players)
{
}

std::string PlayerlistEdit::getHelpMessage()
{
    return "add <name> - add a player.\ndelete <index> - delete a player.\nlist - get list of a players.\n"
           "start - start the game.\n\nYou need at least two players to start the game.";
}

void PlayerlistEdit::addPlayer(std::string playerName)
{
    Player newPlayer(playerName);
    this->players.push_back(newPlayer);
}

void PlayerlistEdit::deletePlayer(size_t playerIndex)
{
    if (playerIndex > this->players.size())
        throw std::range_error("Invalid index");
    this->players.erase(this->players.begin() + playerIndex - 1);
}

void PlayerlistEdit::processCommand(std::string command)
{
    std::string onlyCommand;
    std::string commandArgument;
    bool readingArgument = false;
    for (auto symbol : command)
    {
        if (symbol == ' ')
            readingArgument = true;
        else if (readingArgument)
            commandArgument += symbol;
        else
            onlyCommand += symbol;
    }
    if (onlyCommand == "add")
        this->addPlayer(commandArgument);
    else if (onlyCommand == "list")
    {
        for (size_t index = 0; index < this->players.size(); index++)
        {
            std::cout << index + 1 << ". " << this->players[index].getName() << '\n';
        }
    }
    else if (onlyCommand == "delete")
    {
        size_t index;
        sscanf(commandArgument.c_str(), "%zu", &index);
        try
        {
            this->deletePlayer(index);
        }
        catch (const std::range_error &e)
        {
            std::cout << e.what() << '\n';
        }
    }
    else if (onlyCommand == "start")
    {
        if (this->players.size() < 2)
            std::cout << "You need at least two players to start the game.\n";
        else
            std::cout << "Game starting...\n";
    }
    else
        std::cout << "Unknown command. Type \"help\" for help.\n";
}