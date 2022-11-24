#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Attribute.h"
using namespace std;

// Base Class
Attribute::~Attribute()
{
    delete this;
}

int Attribute::getAmount() { return amount; }

int Attribute::setAmount(int amount) { return amount; }

// Health Attribute

Health::Health(int amount) : amount(amount) {}

int Health::getAmount()
{
    return amount;
}

int Health::setAmount(int value)
{
    return amount += value;
}

// Mana Attribute

Mana::Mana(int amount) : amount(amount) {}

int Mana::getAmount()
{
    return amount;
}

int Mana::setAmount(int value)
{
    return amount += value;
}
