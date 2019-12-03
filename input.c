#include "input.h"
#include "Structs/World.h"
#include "Structs/Circle.h"
#include "Structs/Vec2.h"
#include "graphics.h"
#include "raylib.h"
#include "Structs/PlayerScore.h"
#include <stdio.h>
#include <string.h>

// Updates the input according to the game state
void updateInput(World* w, float delta) {
    switch (w->state) {
    case PLAYING:
        updateInputPlaying(w, delta);
        break;
    case GAME_OVER:
        updateInputGameOver(w, delta);
        break;
    case MAIN_MENU:
        updateInputMainMenu(w, delta);
        break;
    case PAUSE_MENU:
        updateInputPauseMenu(w, delta);
        break;
    case ASK_NAME:
        updateAskName(w, delta);
    case HIGH_SCORE_SCREEN:
        updateHighScoreScreen(w, delta);
        break;
    }
}

// Moves the player to chase the cursor
void movePlayer(World* w, float delta) {
    // Get the mouse position
    Vec2 mousePos = vector2ToVec2(GetScreenToWorld2D(GetMousePosition(), cam));

    // Calculate the angle between the player and the mouse
    float angle = angleBetween(w->player.position, mousePos);

    // Transform the angle into a X and Y motion and multiply it by delta
    Vec2 movement = getMovementByAngle(angle, getCircleSpeed(w->player));
    movement = scaleVec2(movement, delta);

    // Apply the movement to the player
    moveCircle(&w->player, movement);
}

// Converts between raylib Vectors (Vector2) and Hr.io Vectors (Vec2)
Vec2 vector2ToVec2(Vector2 v) {
    return (Vec2) {
        v.x,
        v.y
    };
}

// Update the input on the PLAYING game state
void updateInputPlaying(World *w, float delta) {
    // Move the player
    movePlayer(w, delta);

    // Check for pause
    if (IsKeyPressed(KEY_ESCAPE)) {
        w->state = PAUSE_MENU;
    }
}

// Update the input on the GAME_OVER state
void updateInputGameOver(World* w, float delta) {
    // If the user is clicking
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        // Check if the restart button was pressed
        if (pointInRect(GAME_OVER_BUTTON, GetMousePosition())){
            *w = newWorld(w);
            w->state = PLAYING;

        // Check if the exit button was pressed
        } else if (pointInRect(GAME_OVER_MENU_BUTTON, GetMousePosition())) {
            w->state = MAIN_MENU;
        }
    }
}

// Tells if a point is inside a rectangle
int pointInRect(Rectangle r, Vector2 v) {
    return v.x < r.width + r.x &&
            v.x > r.x &&
            v.y < r.y + r.height &&
            v.y > r.y;
}

// Updates the input for the MAIN_MENU state
void updateInputMainMenu(World* w, float delta) {
    // If the user is clicking...
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Check if the start button was clicked
        if (pointInRect(MAIN_MENU_START_BUTTON, GetMousePosition())){
            // Start a new world, and carry no information from a previous world
            *w = newWorld(NULL);
            w->state = ASK_NAME;

        // If the load button was clicked
        } else if (pointInRect(MAIN_MENU_LOAD_BUTTON, GetMousePosition())) {
            // If loading was successful, start playing
            if (loadWorld(w)) {
               w->state = PLAYING;
            }

        // If the highscore button was clicked, go to the highscore screen
        } else if (pointInRect(MAIN_MENU_HISCORE_BUTTON, GetMousePosition())) {
            w->state = HIGH_SCORE_SCREEN;

        // If the exit button was clicked, tell the game to quit
        } else if (pointInRect(MAIN_MENU_EXIT_BUTTON, GetMousePosition())) {
            isRunning = 0;
        }
    }
}

// Update the input for the pause menu
void updateInputPauseMenu(World* w, float delta) {
    // Go back to playing if the ESC key was pressed
    if (IsKeyPressed(KEY_ESCAPE)) {
        w->state = PLAYING;
    }

    // If the user is clicking...
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        // Check if the resume button was clicked
        if (pointInRect(PAUSE_MENU_RESUME_BUTTON, GetMousePosition())) {
            w->state = PLAYING;
        }
        // Check if the save button was clicked
        if (pointInRect(PAUSE_MENU_SAVE_BUTTON, GetMousePosition())) {
            saveWorld(*w);
        }
        // Check if the exit button was clicked
        if (pointInRect(PAUSE_MENU_EXIT_BUTTON, GetMousePosition())) {
            w->state = MAIN_MENU;
        }
    }
}

// Update the input for the ASK_NAME state
void updateAskName(World* w, float delta) {
    // Get the keu the user is pressing
    int key = GetKeyPressed();

    // User to treat a char as a string of length 1
    char tmp[2] = {0};

    if (key > 0) {
        // If the key is a allowed character...
        if ((key >= '0' && key <= '9') || (key >= 'A' && key <= 'z') || key == ' ') {
            // "Convert" it to a string
            tmp[0] = (char)key;
            // Concatenate it to the player's name
            strcat(w->player.name, tmp);
        }
    }

    // Check for the backspace key
    if (IsKeyPressed(KEY_BACKSPACE)) {
        // Get the index for the last char
        int index = strlen(w->player.name) - 1;

        // If the index is valid, erase that char
        if (index >= 0) {
            w->player.name[index] = '\0';
        }
    }

    // If the user got the mouse over the confirmation button...
    if (pointInRect(ASK_NAME_CONFIRM_BUTTON, GetMousePosition())) {
        // If the user clicked the button and typed a name, start the game
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && strlen(w->player.name) > 0) {
            w->state = PLAYING;
        }
    }
}

// Update the input for the HIGH_SCORE_SCREEN state
void updateHighScoreScreen(World* w, float delta) {
    if (pointInRect(HIGH_SCORE_BACK_BUTTON, GetMousePosition()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        w->state = MAIN_MENU;
    }
}
