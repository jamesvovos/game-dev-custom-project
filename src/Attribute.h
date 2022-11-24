#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
using namespace std;

// Abstract base class

class Attribute
{
private:
    int amount;

public:
    virtual ~Attribute();
    virtual int getAmount();
    virtual int setAmount(int value);
};

// Sub-classes such as health, mana, stamina, etc.

class Health : public Attribute
{
private:
    int amount; // the amount of health available.

public:
    int getAmount() override;
    int setAmount(int value) override;
    // Constructor
    Health(int amount);
};

class Mana : public Attribute
{
private:
    int amount; // the amount of mana available.

public:
    int getAmount() override;
    int setAmount(int value) override;
    // Constructor
    Mana(int amount);
};
