#include <iostream>
#include <conio.h>
#include <stack>
#include "State.h"
#include "CommandProcessor.h"
#include "InputHandler.h"
using namespace std;

class GameManager
{ // this is the StateManager
private:
    stack<State *> _states; // LIFO
public:
    World *_world;
    Player *_player;
    CommandProcessor *_cp = new CommandProcessor(_player, _world);
    InputHandler *_ih = new InputHandler(this);
    // if we have a state, we are running ...
    bool running() const;
    // return the top of LIFO stack!
    State *current();
    // enable adding/removing state instances to stack
    void push_state(State *state);
    void pop_state();

    // get input
    InputHandler *getInputHandler();

    // cleanup
    ~GameManager();

    // constructor - defined after States are defined
    GameManager(World *world, Player *player);
};