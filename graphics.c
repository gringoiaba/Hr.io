#include "graphics.h"
#include "raylib.h"
#include "Structs/Vec2.h"
#include "Structs/Circle.h"
#include "Structs/World.h"
#include "Structs/Enemy.h"
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void initGraphics() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hr.io");
    SetTargetFPS(60);


    cam = (Camera2D) { 0 };
    cam.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    cam.zoom = 1.0f;
}

void drawWorld(World w) {
    int i;

    cam.target = vec2ToVector2(w.player.position);
    cam.zoom += (float)(GetMouseWheelMove() * 0.05f);

    BeginDrawing();

        BeginMode2D(cam);

            ClearBackground(RAYWHITE);


            if (w.player.isAlive) {
                Color c = VIOLET;


                // Make poisoned balls flicker
                int time = (int)(w.player.poisonTimeRemaining * 3);
                if (time % 2 == 1) {
                    // "mix" the colors togehter

                    c = GetColor((ColorToInt(GREEN) + ColorToInt(c)) / 2);
                }

                drawCircle(w.player, c);
            }

            for (i = 0; i < NUM_ENEMIES; i++) {
                if (w.enemies[i].ball.isAlive) {
                    Color c;

                    switch (w.enemies[i].elementalType) {
                    case EXPLOSIVE:
                        c = ORANGE;
                        break;
                    case POISONOUS:
                        c = GREEN;
                        break;
                    case NONE:
                        c = RED;
                        break;
                    }

                    // Make poisoned balls flicker
                    int time = (int)(w.enemies[i].ball.poisonTimeRemaining * 3);
                    if (time % 2 == 1) {
                        // "mix" the colors togehter
                        c = GetColor((ColorToInt(GREEN) + ColorToInt(c)) / 2);
                    }

                    drawCircle(w.enemies[i].ball, c);
                }
            }

            for (i = 0; i < NUM_FOOD; i++) {
                if (w.foods[i].isAlive) {
                    drawCircle(w.foods[i], YELLOW);
                }
            }

        EndMode2D();

    char mensagem[51];
    sprintf(mensagem, "Score: %.1f", w.elapsedTime);

    DrawText(mensagem, 0, 0, 52, BLACK);

    EndDrawing();
}

void drawCircle(Ball b, Color c) {
    DrawCircle(b.position.x, b.position.y, b.radius, c);
}

void endGraphics() {
    CloseWindow();
}

int isGraphicsRunning() {
    return !WindowShouldClose();
}

Vector2 vec2ToVector2(Vec2 v) {
    Vector2 res;

    res.x = v.x;
    res.y = v.y;

    return res;
}
