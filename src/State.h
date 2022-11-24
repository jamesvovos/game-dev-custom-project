#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
using namespace std;

// forward decleration for abstract State
class GameManager;

// Abstract base class with pure virtual methods
class State
{
protected:
    GameManager *_manager = nullptr; // NEW
public:
    virtual void update() = 0; // pure virtual
    virtual void render() = 0;
};

// States -> Inheritance

class QuitGame : public State
{
public:
    void update() override;
    void render() override;

    explicit QuitGame(GameManager *manager);
};

class NewHighScore : public State
{
public:
    void update() override;
    void render() override;

    explicit NewHighScore(GameManager *manager);
};

class Gameplay : public State
{
public:
    bool disable_commands = false;
    bool inventory_open = false;
    bool command_terminal_open = false;
    void update() override;
    void render() override;

    explicit Gameplay(GameManager *manager);
};

class SelectAdventure : public State
{
public:
    void update() override;
    void render() override;

    explicit SelectAdventure(GameManager *manager);
};

class HallOfFame : public State
{
public:
    void update() override;
    void render() override;

    explicit HallOfFame(GameManager *manager);
};

class Help : public State
{
public:
    void update() override;
    void render() override;

    explicit Help(GameManager *manager);
};

class About : public State
{
public:
    void update() override;
    void render() override;

    explicit About(GameManager *manager);
};

class MainMenu : public State
{
public:
    void update() override;
    void render() override;

    explicit MainMenu(GameManager *manager);
};
