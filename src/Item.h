#pragma once
#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "../include/raylib.h"
using namespace std;

// Component virtual base class
class Backpack
{
protected:
    vector<Backpack *> _backpackitems;

public:
    virtual string getName() = 0;
    virtual string getDesc() = 0;
    virtual void displayDetails() = 0;
    virtual ~Backpack() = 0;
    virtual void add(Backpack *b);
    virtual void remove(Backpack *item);
    virtual vector<Backpack *> getItems();
    virtual void render() = 0;
    virtual Texture2D getTexture() = 0;
    virtual Vector2 getPosition() = 0;
};

// Composite of items [for each l : leaf]
class Bag : public Backpack
{
protected:
    vector<Backpack *> _bagitems;
    string _name;
    string _desc;
    Vector2 _position;
    Texture2D _texture;

public:
    string getName() override;
    string getDesc() override;
    void displayDetails() override;
    void render() override;
    Texture2D getTexture() override;
    Vector2 getPosition() override;
    void add(Backpack *b) override;
    void remove(Backpack *item) override;
    vector<Backpack *> getItems() override;
    // Constructor
    Bag(string name, string desc, Vector2 position, Texture2D texture) : _name(name), _desc(desc), _position(position), _texture(texture) {}
    ~Bag();
};

// Leaf
class Item : public Backpack
{
private:
    string _name;
    string _desc;
    Vector2 _position;
    Texture2D _texture;

public:
    string getName() override;
    string getDesc() override;
    void displayDetails() override;
    void render() override;
    Texture2D getTexture() override;
    Vector2 getPosition() override;
    // Constructor
    Item(string name, string desc, Vector2 position, Texture2D texture) : _name(name), _desc(desc), _position(position), _texture(texture) {}
    ~Item();
};