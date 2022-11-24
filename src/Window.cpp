#include <iostream>
#include "Window.h"
#include "GameManager.h"
#include "../include/raylib.h"
using namespace std;

Window::Window(GameManager *manager) : _manager(manager)
{
    // Initialise game window
    InitWindow(windowWidth, windowHeight, "Custom Project");
    SetTargetFPS(60);

    // Have to set the player texture here as we create a player before we call our InitWindow() function.
    Texture2D playerTexture = LoadTexture("../src/assets/sprites/scarfy.png");
    _manager->_player->setTexture(playerTexture);

    // Initialise audio
    InitAudioDevice();
    Music music = LoadMusicStream("../src/assets/audio/menumusic.mp3");
    PlayMusicStream(music);

    // Game loop
    while (!WindowShouldClose())
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music); // Update music buffer with new stream data
        _manager->current()->update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(Color{0, 153, 255, 255});
        _manager->current()->render();
        EndDrawing();
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music); // Unload music stream buffers from RAM
    CloseAudioDevice();       // Close audio device (music streaming is automatically stopped)
    UnloadTexture(playerTexture);
    CloseWindow(); // Close window and OpenGL context
};

Window::~Window()
{
    delete this;
}