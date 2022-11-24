#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Inventory.h"
#include "Player.h"
#include "Location.h"
#include "World.h"
using namespace std;

// References:
// https://refactoring.guru/design-patterns/command/cpp/example#:~:text=Command%20in%20C%2B%2B,Learn%20more%20about%20Command
// https://www.youtube.com/watch?v=yDkIK3JfHkw&t
// https://www.bogotobogo.com/DesignPatterns/command.php

// forward decleration
class CommandProcessor;

// Command Interface
class Command
{
public:
    virtual ~Command();
    virtual void Execute(string input, Player *player);
};

class GoCommand : public Command
{
private:
    stack<string> _movementlog; // logs all past moves on a stack data structure

public:
    void Execute(string input, Player *player) override;

    // Constructor
    GoCommand();
};

class HelpCommand : public Command
{
private:
    bool isLoaded = false;
    vector<string> _availablecommands; // dynamic array of all available commands
public:
    void Execute(string input, Player *player) override;
    bool setIsLoaded();

    // Constructor
    HelpCommand();
};

class InventoryCommand : public Command
{
public:
    void Execute(string input, Player *player) override;

    // Constructor
    InventoryCommand();
};

class LookCommand : public Command
{
public:
    void Execute(string input, Player *player) override;

    // Constructor
    LookCommand();
};

class AttackCommand : public Command
{
public:
    void Execute(string input, Player *player) override;

    // Constructor
    AttackCommand();
};

class TakeCommand : public Command
{
public:
    void Execute(string input, Player *player) override;

    // Constructor
    TakeCommand();
};

class PutCommand : public Command
{
public:
    void Execute(string input, Player *player) override;

    // Constructor
    PutCommand();
};