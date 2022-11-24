#include <iostream>
#include <conio.h>
#include <stack>
#include "GameManager.h"
using namespace std;

// constructor - defined after States are defined
GameManager::GameManager(World *world, Player *player) : _world(world), _player(player)
{
    // add a first state to be ready
    push_state(new MainMenu(this));
}

// if we have a state, we are running ...
bool GameManager::running() const
{
    return !_states.empty();
}

// return the top of LIFO stack!
State *GameManager::current() { return _states.top(); }

// enable adding/removing state instances to stack
void GameManager::push_state(State *state) { _states.push(state); }

void GameManager::pop_state()
{
    _states.pop();
}

// handle user input
InputHandler *GameManager::getInputHandler()
{
    return _ih;
}

// cleanup
GameManager::~GameManager()
{
    while (!_states.empty())
    {
        delete _states.top();
    }
    _cp->~CommandProcessor();
    _ih->~InputHandler();
}