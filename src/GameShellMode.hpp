#ifndef GAMESHELLMODE_HPP
#define GAMESHELLMODE_HPP

#include "BasicShellModes.hpp"
#include "Combinations.hpp"
#include "DiceASCIIArt.hpp"
#include <map>
#include <string>

class GameShellMode : public ShellMode
{
  private:
    bool isUpperSectionPart = true;
    std::vector<Player> &players;
    std::vector<Player>::iterator currentPlayerIterator;
    unsigned currentPlayersRolls = 0;
    unsigned roundsCount = 0;
    const unsigned upperRounds = 6;
    const unsigned lowerRounds = 6;
    std::map<Combination *, std::map<Player *, int>> results;
    const std::string staticHelp = "results - print results table.\n"
                                   "combinations - print table with points, that you can get for each combination\n"
                                   "roll <index1> <index2> ... | all - roll dice.\n"
                                   "write <combination index> - write a result to the table and finish your turn.\n"
                                   "dice - print your dice.\n";
    void updatePlayersData();
    bool playersDataUpdated = false;
    std::string generatePlayerDiceASCIIArt();
    std::string generateResultsTable();
    std::string generateCurrentPlayerCombinationsTable();

  public:
    GameShellMode(std::vector<Player> &players);
    std::string getHelpMessage() override final;
    void processCommand(std::string command, GameShell &shell) override final;
};

#endif // GAMESHELLMODE_HPP
