#include <iostream>
#include <conio.h>
#include <stack>
#include <vector>
#include "Enemy.h"
#include "Attribute.h"
#include "../include/raylib.h"
#include "../include/raymath.h"
using namespace std;

// Implementation idea from lecture slides:
Enemy::Enemy(string _name, string _desc, Vector2 _position, Texture2D _texture, Vector2 _target) : name(_name), desc(_desc), position(_position), texture(_texture), target(_target) {}

Enemy::~Enemy()
{
    UnloadTexture(texture);
    delete this;
}

// Debugging stuff
void Enemy::print()
{
    printf("I have ...\n");
    for (auto &a : attributes)
    {
        printf("- %s %d\n", a.first.c_str(), a.second);
    }
    printf("I can do ...\n");
    for (const auto &a : actions)
    {
        printf("- %s\n", a.first.c_str());
    }
    printf("\n");
}

void Enemy::update()
{
    int npc_pos = 120;
    if (round(position.x - npc_pos) != round(target.x))
    {
        position.x -= 5;
    }
    else
    {
        standing_infront_of_player = true;
    }
}

void Enemy::render()
{
    // healthbar stuff -> https://www.youtube.com/watch?v=pUEZbUAMZYA
    int currentHP = attributes["health"];
    int maxHealth = 100;
    int healthBarLength = 100;
    float healthRatio = maxHealth / healthBarLength;

    // if enemy has hp, means alive -> display the enemy on screen
    if (attributes["health"] > 0)
    {
        DrawTextureRec(texture, Rectangle{0, 0, (float)texture.width, (float)texture.height}, position, RAYWHITE); // draws the enemy sprite
        DrawText(name.c_str(), position.x, position.y - 60, 20, WHITE);                                            // draws enemy name
        DrawRectangle(position.x, position.y - 40, currentHP / healthRatio, 32, RED);                              // draws enemy health bar
        DrawText(to_string(attributes["health"]).c_str(), position.x, position.y - 30, 20, WHITE);                 // draws enemy health amount

        // if enemy NPC has wondered up to the player, display text/speech box.
        if (standing_infront_of_player == true)
        {
            if (sound_played == false)
            {
                Sound sound = LoadSound("../src/assets/audio/enemy_sound.wav");
                PlaySound(sound);
                sound_played = true;
            }
            if (name == "dark magician")
            {
                DrawRectangle(position.x, position.y - 80, 460, 24, BLACK);
                DrawText(desc.c_str(), position.x + 5, position.y - 80, 20, RED);
            }
            if (name == "troll")
            {
                DrawRectangle(position.x, position.y - 80, 300, 24, BLACK);
                DrawText(desc.c_str(), position.x + 5, position.y - 80, 20, RED);
            }
        }
    }
}