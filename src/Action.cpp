#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Enemy.h"
#include "Action.h"
using namespace std;

// Implementation idea from lecture slides:

Action::~Action()
{
    delete this;
}

// FireBall Action

FireBall::FireBall(Enemy *enemy) : Action(enemy) {}

FireBall::~FireBall()
{
    delete this;
}

void FireBall::Execute()
{
    if (_enemy->attributes.count("mana") && _enemy->attributes.count("health"))
    {
        Sound sound = LoadSound("../src/assets/audio/fire_explosion.wav");
        PlaySound(sound);
        printf("... casting fire ball! ouch.\n");
        _enemy->attributes["mana"] -= mana_cost;
        _enemy->attributes["health"] -= health_cost;
    }
    else
    {
        printf("... I don't have what I need to cast a fireball.\n");
    }
}
