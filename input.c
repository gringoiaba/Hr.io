#include "input.h"
#include "Structs/World.h"
#include "Structs/Circle.h"
#include "Structs/Vec2.h"
#include "graphics.h"
#include "raylib.h"
#include <stdio.h>

#define PLAYER_SPEED 100

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
    }
}

void movePlayer(World* w, float delta) {
    Vec2 mousePos = vector2ToVec2(GetScreenToWorld2D(GetMousePosition(), cam));

    float angle = angleBetween(w->player.position, mousePos);

    Vec2 movement = getMovementByAngle(angle, PLAYER_SPEED);
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
            w->state = PLAYING;

        } else if (pointInRect(MAIN_MENU_LOAD_BUTTON, GetMousePosition())) {
            // TODO: Load
            // *w = loadWorld();
            w->state = PLAYING;

        } else if (pointInRect(MAIN_MENU_HISCORE_BUTTON, GetMousePosition())) {
            // TODO: Hiscore state
            // w->state = HISCORE;

        } else if (pointInRect(MAIN_MENU_EXIT_BUTTON, GetMousePosition())) {
            isRunning = 0;
        }
    }
}

void updateInputPauseMenu(World* w, float delta) {
    if (IsKeyPressed(KEY_ESCAPE)) {
        w->state = PLAYING;
    }

}
