#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include <map>
#include "Attribute.h"
#include "Enemy.h"
using namespace std;

// forward decleration
class Enemy;

class Action
{
protected:
    Enemy *_enemy;
    int health_cost = 50;
    int mana_cost = 10;

public:
    virtual void Execute() = 0;
    explicit Action(Enemy *enemy) { _enemy = enemy; }
    virtual ~Action() = 0;
};

class FireBall : public Action
{
public:
    explicit FireBall(Enemy *enemy);
    void Execute() override;
    ~FireBall();
};