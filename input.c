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
}

void updateInputGameOver(World* w, float delta) {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && pointInRect(GAME_OVER_BUTTON, GetMousePosition())){
        *w = newWorld();
        w->state = PLAYING;
    }
}

int pointInRect(Rectangle r, Vector2 v) {
    return v.x < r.width + r.x &&
            v.x > r.x &&
            v.y < r.y + r.height &&
            v.y > r.y;
}
