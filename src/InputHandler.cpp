#include <iostream>
#include "InputHandler.h"
#include "GameManager.h"
#include "../include/raylib.h"
using namespace std;

// Resources used for this class: https://www.raylib.com/examples/text/loader.html?name=text_input_box

InputHandler::InputHandler(GameManager *manager) : _manager(manager) {}

InputHandler::~InputHandler()
{
    delete this;
}

void InputHandler::render()
{
    // DrawText("PLACE MOUSE OVER INPUT BOX!", 240, 140, 20, BLACK);
    DrawRectangleRec(textBox, LIGHTGRAY);
    if (mouseOnText)
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLUE);
    else
        DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, BLACK);

    DrawText(command, (int)textBox.x + 5, (int)textBox.y + 8, 40, BLUE);

    // DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 315, 250, 20, BLACK);
    DrawText("Enter a [Command]", 315, 250, 20, BLACK);

    if (mouseOnText)
    {
        if (letterCount < MAX_INPUT_CHARS)
        {
            // Draw blinking underscore char
            if (((framesCounter / 20) % 2) == 0)
                DrawText("_", (int)textBox.x + 8 + MeasureText(command, 40), (int)textBox.y + 12, 40, BLUE);
        }
        else
            DrawText("Press BACKSPACE to delete chars...", 230, 300, 20, GRAY);
    }
}

void InputHandler::update()
{
    if (CheckCollisionPointRec(GetMousePosition(), textBox))
        mouseOnText = true;
    else
        mouseOnText = false;

    if (mouseOnText)
    {
        // Set the window's cursor to the I-Beam
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        // Get char pressed (unicode character) on the queue
        int key = GetCharPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            // NOTE: Only allow keys in range [32..125]
            if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS))
            {
                command[letterCount] = (char)key;
                command[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
                letterCount++;
            }

            key = GetCharPressed(); // Check next character in the queue
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            letterCount--;
            if (letterCount < 0)
                letterCount = 0;
            command[letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            _manager->_cp->runCommand(command); // needs access to the CommandProcessor
        }
    }
    else
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    if (mouseOnText)
        framesCounter++;
    else
        framesCounter = 0;
}

// Check if any key is pressed
// NOTE: We limit keys check to keys between 32 (KEY_SPACE) and 126
bool InputHandler::IsAnyKeyPressed()
{
    bool keyPressed = false;
    int key = GetKeyPressed();

    if ((key >= 32) && (key <= 126))
        keyPressed = true;

    return keyPressed;
}
