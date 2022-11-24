#include <iostream>
#include <conio.h>
#include <stack>
#include <sstream>
#include "CommandProcessor.h"
using namespace std;

// References: https://refactoring.guru/design-patterns/command/cpp/example#:~:text=Command%20in%20C%2B%2B,Learn%20more%20about%20Command

void CommandProcessor::runCommand(string input)
{
    stringstream ss(input);
    string cmd, remaining;

    getline(ss, cmd, ' ');
    getline(ss, remaining);

    if (commands.find(cmd) != commands.end())
    {
        commands[cmd]->Execute(remaining, player);
    }
    else
    {
        cout << "Command not recognised!" << endl;
    }
}

void CommandProcessor::showCommands()
{
    for (auto c : commands)
    {
        cout << c.first;
    }
}

CommandProcessor::~CommandProcessor()
{
    for (auto c : commands)
    {
        delete c.second;
    }
    delete this;
}

CommandProcessor::CommandProcessor(Player *player, World *world) : player(player), world(world)
{
    commands["help"] = new HelpCommand();
    commands["go"] = new GoCommand();
    commands["inventory"] = new InventoryCommand();
    commands["look"] = new LookCommand();
    commands["attack"] = new AttackCommand();
    commands["take"] = new TakeCommand();
    commands["put"] = new PutCommand();
}