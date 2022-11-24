#include <iostream>
#include <conio.h>
#include <stack>
#include "State.h"
#include "GameManager.h"
#include "../include/raylib.h"
using namespace std;

// QuitGame State

void QuitGame::update()
{
    _manager->~GameManager(); // clean up objects in memory
    _manager->_world->~World();
}

void QuitGame::render()
{
    DrawText(">> Thus ends another grand Adventure for Scarfy.", 190, 80, 20, LIGHTGRAY);
}

QuitGame::QuitGame(GameManager *manager)
{
    _manager = manager;
}

// NewHighScore State

void NewHighScore::update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        _manager->pop_state();
        _manager->pop_state();
        _manager->pop_state();
    }
}

void NewHighScore::render()
{
    DrawText("The Adventures of Scarfy :: New High Score", 190, 80, 20, LIGHTGRAY);
    DrawText("-------------------------------------------------------- ", 190, 100, 20, LIGHTGRAY);
    DrawText("Congratulations!", 190, 120, 20, LIGHTGRAY);
    DrawText("You have made it to the Adventures of Scarfy Hall Of Fame.", 190, 140, 20, LIGHTGRAY);
    DrawText("Adventure: [the adventure world played]", 190, 160, 20, LIGHTGRAY);
    DrawText("Score: [the players score]", 190, 180, 20, LIGHTGRAY);
    DrawText("Moves: [number of moves player made]", 190, 200, 20, LIGHTGRAY);
    DrawText("Please type your name and press enter:", 190, 220, 20, LIGHTGRAY);
}

NewHighScore::NewHighScore(GameManager *manager)
{
    _manager = manager;
}

// Gameplay State

void Gameplay::update()
{
    // go back to main menu without restarting game state
    if (IsKeyPressed(KEY_B) && disable_commands == false)
    {
        _manager->pop_state();
        _manager->pop_state();
    }
    if (IsKeyPressed(KEY_ESCAPE) && disable_commands == false)
    {
        _manager->push_state(new QuitGame(_manager));
    }
    if (IsKeyPressed(KEY_N) && disable_commands == false)
    {
        _manager->push_state(new NewHighScore(_manager));
    }
    if (IsKeyPressed(KEY_I) && disable_commands == false)
    {
        // open/close the player inventory UI
        inventory_open = !inventory_open;
        if (inventory_open == true)
        {
            Sound sound = LoadSound("../src/assets/audio/ring_inventory.wav");
            PlaySound(sound);
        }
    }
    if (IsKeyPressed(KEY_A) && disable_commands == false || (KEY_D) && disable_commands == false)
    {
        // player movement
        _manager->_cp->runCommand("go");
    }
    if (IsKeyPressed(KEY_TAB))
    {
        // command terminal open/closed
        command_terminal_open = !command_terminal_open;
        // disable movement commands etc
        disable_commands = !disable_commands;
    }
    if (command_terminal_open == true)
    {
        _manager->getInputHandler()->update(); // change this to handle input command or something?
    }
    // check to see if the player is moving to different location nodes via the doors
    _manager->_player->checkIfGoingThroughDoor();
    _manager->_world->update();
}

void Gameplay::render()
{
    // Render the current location
    _manager->_player->getCurrentLocation()->render();
    // Render the player
    _manager->_player->render();
    // Draw the inventory UI
    if (inventory_open == true)
    {
        _manager->_cp->runCommand("inventory");
    }
    if (command_terminal_open == true)
    {
        _manager->getInputHandler()->render(); // change this to handle input command or something?
    }
    _manager->_cp->runCommand("look");
}

Gameplay::Gameplay(GameManager *manager)
{
    _manager = manager;
}

// SelectAdventure State

void SelectAdventure::update()
{
    if (IsKeyPressed(KEY_ONE))
    {
        // read values from file
        ifstream myFile;
        _manager->_world->load_file(myFile);
        _manager->push_state(new Gameplay(_manager));
    }
}

void SelectAdventure::render()
{
    DrawText("The Adventures of Scarfy :: Select Adventure", 190, 80, 20, LIGHTGRAY);
    DrawText("-------------------------------------------------------- ", 190, 100, 20, LIGHTGRAY);
    DrawText("Choose your adventure:", 190, 120, 20, LIGHTGRAY);
    DrawText("1. Mountain Portal World", 190, 140, 20, LIGHTGRAY);
}

SelectAdventure::SelectAdventure(GameManager *manager)
{
    _manager = manager;
}

// HallOfFame State

void HallOfFame::update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        _manager->pop_state();
    }
}
void HallOfFame::render()
{
    DrawText("The Adventures of Scarfy :: Hall Of Fame", 190, 80, 20, LIGHTGRAY);
    DrawText("-------------------------------------------------------- ", 190, 100, 20, LIGHTGRAY);
    DrawText("1. Fred, Mountain World, 5000", 190, 120, 20, LIGHTGRAY);
    DrawText("2. Mary, Mountain World, 4000", 190, 140, 20, LIGHTGRAY);
    DrawText("3. Joe, Water World, 3000", 190, 160, 20, LIGHTGRAY);
    DrawText("4. Henry, Mountain World, 2000", 190, 180, 20, LIGHTGRAY);
    DrawText("5. Susan, Mountain World, 1000", 190, 200, 20, LIGHTGRAY);
    DrawText("6. Alfred, Water World, 900", 190, 220, 20, LIGHTGRAY);
    DrawText("Press Enter to return to the Main Menu", 190, 240, 20, LIGHTGRAY);
}

HallOfFame::HallOfFame(GameManager *manager)
{
    _manager = manager;
}

// Help State

void Help::update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        _manager->pop_state();
    }
}
void Help::render()
{
    _manager->_cp->runCommand("help");
}

Help::Help(GameManager *manager)
{
    _manager = manager;
}

// About State

void About::update()
{
    if (IsKeyPressed(KEY_ENTER))
    {
        _manager->pop_state();
    }
}
void About::render()
{
    DrawText("The Adventures of Scarfy :: About", 190, 80, 20, LIGHTGRAY);
    DrawText("-------------------------------------------------------- ", 190, 100, 20, LIGHTGRAY);
    DrawText("Written by: James Vovos", 190, 120, 20, LIGHTGRAY);
    DrawText("Press Enter to return to the Main Menu", 190, 140, 20, LIGHTGRAY);
}

About::About(GameManager *manager)
{
    _manager = manager;
}

// MainMenu State

void MainMenu::update()
{
    if (IsKeyPressed(KEY_ONE))
    {
        _manager->push_state(new SelectAdventure(_manager));
    }
    if (IsKeyPressed(KEY_TWO))
    {
        _manager->push_state(new HallOfFame(_manager));
    }
    if (IsKeyPressed(KEY_THREE))
    {
        _manager->push_state(new Help(_manager));
    }
    if (IsKeyPressed(KEY_FOUR))
    {
        _manager->push_state(new About(_manager));
    }
    if (IsKeyPressed(KEY_FIVE))
    {
        _manager->push_state(new QuitGame(_manager));
    }
}
void MainMenu::render()
{
    DrawText("The Adventures of Scarfy :: Main Menu", 190, 80, 20, LIGHTGRAY);
    DrawText("-------------------------------------------------------- ", 190, 100, 20, LIGHTGRAY);
    DrawText("Welcome to The Adventures of Scarfy", 190, 120, 20, LIGHTGRAY);
    DrawText("1. Select Adventure and Play", 190, 140, 20, LIGHTGRAY);
    DrawText("2. Hall Of Fame", 190, 160, 20, LIGHTGRAY);
    DrawText("3. Help", 190, 180, 20, LIGHTGRAY);
    DrawText("4. About", 190, 200, 20, LIGHTGRAY);
    DrawText("5. Quit", 190, 220, 20, LIGHTGRAY);
    DrawText("Select 1-5:>", 190, 240, 20, LIGHTGRAY);
}
MainMenu::MainMenu(GameManager *manager)
{
    _manager = manager;
}