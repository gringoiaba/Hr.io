#include "input.h"
#include "Structs/World.h"
#include "Structs/Circle.h"
#include "Structs/Vec2.h"
#include "graphics.h"
#include "raylib.h"
#include "Structs/PlayerScore.h"
#include <stdio.h>

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

void movePlayer(World* w, float delta) {
    Vec2 mousePos = vector2ToVec2(GetScreenToWorld2D(GetMousePosition(), cam));

    float angle = angleBetween(w->player.position, mousePos);

    Vec2 movement = getMovementByAngle(angle, getCircleSpeed(w->player));
    movement = scaleVec2(movement, delta);

    moveCircle(&w->player, movement);
}

Vec2 vector2ToVec2(Vector2 v) {
    return (Vec2) {
        v.x,
        v.y
    };
}

void updateInputPlaying(World *w, float delta) {
    movePlayer(w, delta);

    if (IsKeyDown(KEY_SPACE)) {
        w->player.radius += delta * 10;
    }

    if (IsKeyPressed(KEY_ESCAPE)) {
        w->state = PAUSE_MENU;
    }
}

void updateInputGameOver(World* w, float delta) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        if (pointInRect(GAME_OVER_BUTTON, GetMousePosition())){
            *w = newWorld();
            w->state = PLAYING;

        } else if (pointInRect(GAME_OVER_MENU_BUTTON, GetMousePosition())) {
            w->state = MAIN_MENU;
        }
    }
}

int pointInRect(Rectangle r, Vector2 v) {
    return v.x < r.width + r.x &&
            v.x > r.x &&
            v.y < r.y + r.height &&
            v.y > r.y;
}

void updateInputMainMenu(World* w, float delta) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        if (pointInRect(MAIN_MENU_START_BUTTON, GetMousePosition())){
            *w = newWorld();
            w->state = ASK_NAME;

        } else if (pointInRect(MAIN_MENU_LOAD_BUTTON, GetMousePosition())) {
            if (loadWorld(w)) {
               w->state = PLAYING;
            }

        } else if (pointInRect(MAIN_MENU_HISCORE_BUTTON, GetMousePosition())) {
            w->state = HIGH_SCORE_SCREEN;

        } else if (pointInRect(MAIN_MENU_EXIT_BUTTON, GetMousePosition())) {
            isRunning = 0;
        }
    }
}

void updateInputPauseMenu(World* w, float delta) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        w->state = PLAYING;
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (pointInRect(PAUSE_MENU_RESUME_BUTTON, GetMousePosition())) {
            w->state = PLAYING;
        }
        if (pointInRect(PAUSE_MENU_SAVE_BUTTON, GetMousePosition())) {
            saveWorld(*w);
        }
        if (pointInRect(PAUSE_MENU_EXIT_BUTTON, GetMousePosition())) {
            w->state = MAIN_MENU;
        }
    }
}

void updateAskName(World* w, float delta) {

    int key = GetKeyPressed();

    char tmp[2] = {0};

    if (key > 0) {
        // If the key is a letter...
        if (key >= 'A' && key <= 'z') {
            tmp[0] = (char)key;
            strcat(w->player.name, tmp);
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        int index = strlen(w->player.name) - 1;

        if (index >= 0) {
            w->player.name[index] = '\0';
        }
    }

    if (pointInRect(ASK_NAME_CONFIRM_BUTTON, GetMousePosition())) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && strlen(w->player.name) > 0) {
            strcat(w->player.name, " ");
            w->state = PLAYING;
        }
    }
}

void updateHighScoreScreen(World* w, float delta) {
    if (pointInRect(HIGH_SCORE_BACK_BUTTON, GetMousePosition()) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        w->state = MAIN_MENU;
    }
}
