#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Item.h"
using namespace std;

class Inventory
{
private:
    vector<Backpack *> _items; // dynamic array
public:
    void displayInventory();
    void addItem(Backpack *item);
    void removeItem(Backpack *item);
    vector<Backpack *> getItems();

    // cleanup
    ~Inventory();

    // constructor
    Inventory();
};