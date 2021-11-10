#include "GameShellMode.hpp"
#include "GameShell.hpp"

std::string generateTable(std::vector<std::vector<std::string>> &values)
{
    std::vector<size_t> columnsSizes;
    for (auto row : values)
    {
        if (columnsSizes.size() < row.size())
            columnsSizes.resize(row.size(), 0);

        for (size_t columnIndex = 0; columnIndex < row.size(); columnIndex++)
            columnsSizes[columnIndex] = std::max(columnsSizes[columnIndex], row[columnIndex].length());
    }
    std::string horizontalSeparator = "+";
    for (auto columnSize : columnsSizes)
    {
        std::string dashes(columnSize + 2, '-');
        horizontalSeparator += dashes + '+';
    }
    std::string result = horizontalSeparator;
    for (auto row : values)
    {
        result += "\n|";
        for (size_t colIndex = 0; colIndex < row.size(); colIndex++)
        {
            std::string cellContent = row[colIndex];
            cellContent.resize(columnsSizes[colIndex], ' ');
            result += ' ' + cellContent + " |";
        }
        for (size_t colIndex = row.size(); colIndex < columnsSizes.size(); colIndex++)
        {
            std::string plug(columnsSizes[colIndex], ' ');
            result += ' ' + plug + " |";
        }
        result += '\n' + horizontalSeparator;
    }
    return result + '\n';
}

GameShellMode::GameShellMode(std::vector<Player> &players) : players(players)
{
}

void GameShellMode::updatePlayersData()
{
    if (!this->playersDataUpdated)
    {
        this->playersDataUpdated = true;
        this->currentPlayerIterator = this->players.begin();
        for (auto &player : this->players)
        {
            for (auto &combination : upperCombinations)
                this->results[combination][&player] = INT_MAX;
            for (auto &combination : lowerCombinations)
                this->results[combination][&player] = INT_MAX;
        }
        std::cout << this->results.size() << '\n';
    }
}

std::string GameShellMode::getHelpMessage()
{
    this->updatePlayersData();
    std::string combinationsPart;
    if (this->isUpperSectionPart)
        combinationsPart = "Upper combinations.";
    else
        combinationsPart = "Lower combinarions.";
    return this->staticHelp + "\n\n" + combinationsPart +
           "\nRolling player: " + this->currentPlayerIterator->getName() + '\n' +
           std::to_string(this->currentPlayersRolls) + "/3 attemps.\n";
}

std::string GameShellMode::generateCurrentPlayerCombinationsTable()
{
    const std::vector<Combination *> *combinations;
    if (this->isUpperSectionPart)
        combinations = &upperCombinations;
    else
        combinations = &lowerCombinations;

    std::vector<std::vector<std::string>> tableValues(2);
    unsigned counter = 1;
    for (auto &combination : *combinations)
    {
        tableValues[0].push_back(std::to_string(counter) + ". " + combination->getName());
        counter++;
        if (this->results[combination][&(*this->currentPlayerIterator)] == INT_MAX)
            tableValues[1].push_back(std::to_string(combination->check(this->currentPlayerIterator->dice)));
        else
            tableValues[1].push_back("");
    }
    return generateTable(tableValues);
}

DiceASCIIArt diceASCIIArt;

std::string GameShellMode::generatePlayerDiceASCIIArt()
{
    std::vector<unsigned> diceNumbers;
    for (auto oneDice : this->currentPlayerIterator->dice)
        diceNumbers.push_back(oneDice.getLastRoll());
    return diceASCIIArt.generate(diceNumbers);
}

void GameShellMode::processCommand(std::string command, GameShell &shell)
{
    std::string onlyCommand;
    std::string commandArgument;
    bool readingArgument = false;
    for (auto symbol : command)
    {
        if (symbol == ' ' && !readingArgument)
            readingArgument = true;
        else if (readingArgument)
            commandArgument += symbol;
        else
            onlyCommand += symbol;
    }
    if (onlyCommand == "results")
        std::cout << this->generateResultsTable() << '\n';
    else if (onlyCommand == "combinations")
    {
        std::cout << this->generateCurrentPlayerCombinationsTable() << '\n';
    }
    else if (onlyCommand == "dice")
    {
        std::cout << this->generatePlayerDiceASCIIArt() << '\n';
    }
    else if (onlyCommand == "roll")
    {
        if (this->currentPlayersRolls == 3)
        {
            std::cout << "You have already used all your attemts for this turn. Write your result to the table.\n";
            return;
        }
        if (commandArgument == "all")
        {
            for (auto &oneDice : this->currentPlayerIterator->dice)
                oneDice.roll();
        }
        else
        {
            std::vector<std::string> commandArgs(1);
            for (auto &symbol : commandArgument)
            {
                if (symbol == ' ')
                {
                    commandArgs.push_back("");
                }
                else
                    commandArgs.back() += symbol;
            }
            std::vector<size_t> diceToRollIndexes;
            for (auto &commandArg : commandArgs)
            {
                size_t index;
                sscanf(commandArg.c_str(), "%zu", &index);
                if (index > 0 && index <= this->currentPlayerIterator->dice.size())
                    diceToRollIndexes.push_back(index - 1);
                else
                {
                    std::cout << "Invalind indexes. Try numbers from 1 to 5.\n";
                    return;
                }
            }
            for (auto diceIndex : diceToRollIndexes)
                this->currentPlayerIterator->dice[diceIndex].roll();
        }
        this->currentPlayersRolls++;
        std::cout << this->generatePlayerDiceASCIIArt() << '\n'
                  << std::to_string(this->currentPlayersRolls) + "/3 attempts used.\n";
    }
    else if (onlyCommand == "write")
    {
        const std::vector<Combination *> *combinations;
        if (this->isUpperSectionPart)
            combinations = &upperCombinations;
        else
            combinations = &lowerCombinations;

        size_t index;
        sscanf(commandArgument.c_str(), "%zu", &index);

        if (index > 0 && index <= combinations->size())
        {
            Combination *combination = (*combinations)[index - 1];
            if (this->results[combination][&(*this->currentPlayerIterator)] == INT_MAX)
            {
                this->results[combination][&(*this->currentPlayerIterator)] =
                    combination->check(this->currentPlayerIterator->dice);
                this->currentPlayerIterator++;
                this->currentPlayersRolls = 0;
                std::cout << this->generateResultsTable() << '\n';
                if (this->currentPlayerIterator == this->players.end())
                {
                    if (this->isUpperSectionPart)
                    {
                        this->roundsCount++;
                        if (this->roundsCount >= this->upperRounds)
                        {
                            this->isUpperSectionPart = false;
                            this->roundsCount = 0;
                        }
                        this->currentPlayerIterator = this->players.begin();
                    }
                    else
                    {
                        shell.stopShell();
                        return;
                    }
                }
                std::cout << this->getHelpMessage() << '\n';
            }
            else
            {
                std::cout << "You have already used this combination. Try others.\n";
                return;
            }
        }
        else
        {
            std::cout
                << "Invalid index. Try positive number. To watch all available combinations, type \"combinations\".\n";
            return;
        }
    }
    else
        throw 0;
}

std::string GameShellMode::generateResultsTable()
{
    std::vector<std::vector<std::string>> tableValues;
    tableValues.push_back(std::vector<std::string>());
    tableValues.back().push_back("");
    for (auto player : this->players)
        tableValues.back().push_back(player.getName());
    auto processCombinations = [&tableValues, this](const std::vector<Combination *> combinations) {
        for (auto combination : combinations)
        {
            tableValues.push_back(std::vector<std::string>());
            tableValues.back().push_back(combination->getName());
            for (auto &player : this->players)
            {
                if (this->results[combination][&player] == INT_MAX)
                    tableValues.back().push_back("");
                else
                    tableValues.back().push_back(std::to_string(this->results[combination][&player]));
            }
        }
    };
    processCombinations(upperCombinations);
    tableValues.push_back(std::vector<std::string>());
    processCombinations(lowerCombinations);
    return generateTable(tableValues);
}