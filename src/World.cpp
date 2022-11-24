#include <iostream>
#include <conio.h>
#include <fstream>
#include <map>
#include <vector>
#include <cstring>
#include <ranges>
#include <algorithm>
#include "World.h"
#include "Enemy.h"
#include "Attribute.h"
#include "../include/json.hpp"
using json = nlohmann::json;
#include "../include/raylib.h"
using namespace std;

World::World(Player *player) : player(player) {}

void World::add_location(const string &id, const string &name, const string &desc, const Vector2 &pos, const Texture2D &texture)
{
    vmap::iterator itr = locations.find(name); // Finding locations (locations) by name
    if (itr == locations.end())
    {
        Location *n;
        n = new Location(id, name, desc, pos, texture); // Creates new location if not already in locations<map> list
        locations[name] = n;
        start_location = locations["a mountain"]; // Set the starting location to the first node
        player->setCurrentLocation(start_location);
        return;
    }
    // for debugging
    printf("Nope, Location [%s] already exists!\n", name.c_str());
};

void World::add_connection(const string &from, const string &to, string direction)
{
    Location *f = (locations.find(from)->second);
    Location *t = (locations.find(to)->second);
    pair<string, Location *> edge = make_pair(direction, t);
    f->adj.push_back(edge);
};

void World::load_file(ifstream &file) // reads location data from file and loads location objects into locations <map> dictionary
{
    if (fileLoaded == false)
    {
        file.open("../src/Adventure.json", ios::in);

        json data = json::parse(file);
        json world = data["world"];
        json locations = world["locations"];
        json connections = world["connections"];
        json items = world["items"];
        json enemies = world["enemies"];
        json bag = world["bag"];
        json doors = world["doors"];

        // Add Locations to World First
        for (auto &loc : locations.items())
        {

            string id = (loc.value())["id"];
            string name = (loc.value())["name"];
            string description = (loc.value())["description"];
            // vector<string> connections = (loc.value())["connection"];
            string texture = (loc.value())["texture"];

            Vector2 pos = {0, 0}; // take up full screen for scene background
            Texture2D locationTexture = LoadTexture(texture.c_str());

            // add locations to graph
            this->add_location(id, name, description, pos, locationTexture);
        }

        // Then add Connections between Location Nodes
        for (auto &c : connections.items())
        {
            string from = (c.value())["from"];
            vector<string> to = (c.value())["to"];

            for (auto t : to)
            {
                istringstream ss(t);
                string token;
                vector<string> connection;
                while (getline(ss, token, ':'))
                {
                    connection.push_back(token);
                    //  For debugging
                    // cout << token << endl;
                }
                this->add_connection(from, connection.at(1), connection.at(0));
            }
        }

        // Add Items to World
        for (auto &i : items.items())
        {
            string name = (i.value())["name"];
            string desc = (i.value())["description"];
            string atLocation = (i.value())["atLocation"];
            float posX = (i.value())["posX"];
            float posY = (i.value())["posY"];
            string texture = (i.value())["texture"];

            Vector2 pos = {posX, posY};
            Texture2D itemTexture = LoadTexture(texture.c_str());

            Item *itm = new Item(name, desc, pos, itemTexture); // Create new Item object
            // player->addItemToInventory(itm);

            // adds items to locations

            for (auto l : this->locations)
            {
                if (l.second->name == atLocation)
                {
                    l.second->addItem(itm);
                }
            }
        }

        // Add Bag to World
        for (auto &b : bag.items())
        {
            string name = (b.value())["name"];
            string desc = (b.value())["description"];
            string atLocation = (b.value())["atLocation"];
            float posX = (b.value())["posX"];
            float posY = (b.value())["posY"];
            string texture = (b.value())["texture"];

            Vector2 pos = {posX, posY};
            Texture2D bagTexture = LoadTexture(texture.c_str());

            Bag *bag = new Bag(name, desc, pos, bagTexture); // Create new Bag object

            // adds bag to location

            for (auto l : this->locations)
            {
                if (l.second->name == atLocation)
                {
                    l.second->addItem(bag);
                    bag->add(l.second->_items.at(0)); // Adding an item to a bag
                }
            }
        }

        // Add Enemies to locations
        for (auto &e : enemies.items())
        {
            string name = (e.value())["name"];
            string desc = (e.value())["description"];
            string atLocation = (e.value())["atLocation"];
            float posX = (e.value())["posX"];
            float posY = (e.value())["posY"];
            string texture = (e.value())["texture"];

            Vector2 pos = {posX, posY};
            Texture2D enemyTexture = LoadTexture(texture.c_str());
            Vector2 target = this->player->getPosition();

            Enemy *ene = new Enemy(name, desc, pos, enemyTexture, target); // Create new Enemy object

            // Hard coding attributes and actions for the "enemy" entity.
            ene->attributes["health"] = 100;
            ene->attributes["mana"] = 100;
            ene->actions["fireball"] = new FireBall(ene);

            // adds enemies to locations
            for (auto l : this->locations)
            {
                if (l.second->name == atLocation)
                {
                    l.second->addEnemy(ene);
                }
            }
        }

        // Add Doors to World
        for (auto &d : doors.items())
        {
            string atLocation = (d.value())["atLocation"];
            float posX = (d.value())["posX"];
            float posY = (d.value())["posY"];
            string texture = (d.value())["texture"];

            Vector2 pos = {posX, posY};
            Texture2D doorTexture = LoadTexture(texture.c_str());

            Door *door = new Door(pos, doorTexture); // Create new Door object

            // adds doors to locations

            for (auto l : this->locations)
            {
                if (l.second->name == atLocation)
                {
                    l.second->addDoor(door);
                }
            }
        }
        file.close();
        setFileLoaded();
    }
    else
    {
        cout << "File is already loaded in..." << endl;
    }
}

bool World::setFileLoaded()
{
    return fileLoaded = true;
}

// Updates enemy positions
void World::update()
{
    for (auto l : locations)
    {
        for (auto e : l.second->_enemies)
        {
            if (l.second == player->getCurrentLocation())
                e->update();
        }
    }
}

World::~World()
{
    for (auto l : locations)
    {
        l.second->~Location();
    }
}