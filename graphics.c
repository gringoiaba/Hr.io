#include "graphics.h"
#include "raylib.h"
#include "Structs/Vec2.h"
#include "Structs/Circle.h"
#include "Structs/World.h"
#include "Structs/Enemy.h"
#include <stdio.h>
#include "input.h"

Font alagard;

void initGraphics() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hr.io");
    SetTargetFPS(60);

    alagard = LoadFont("res/alagard.png");


    cam = (Camera2D) { 0 };
    cam.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    cam.zoom = 1.0f;
}

void drawWorld(World w) {

    BeginDrawing();

    ClearBackground(RAYWHITE);

    switch (w.state) {
    case PLAYING:
        drawPlaying(w, 1);
        break;
    case GAME_OVER:
        drawGameOver(w);
        break;
    }

    EndDrawing();
}

void drawPlaying(World w, int showScore) {
    int i;

    cam.target = vec2ToVector2(w.player.position);
    cam.zoom += (float)(GetMouseWheelMove() * 0.05f);



        BeginMode2D(cam);


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

    if (showScore) {
        char mensagem[51];
        sprintf(mensagem, "Score: %.1f", w.elapsedTime);

        DrawText(mensagem, 0, 0, 52, BLACK);
    }
}

void drawGameOver(World w) {
    drawPlaying(w, 0);

    // Make the world a bit darker
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.1));

    char totalPoints[51];
    sprintf(totalPoints, "Your total score was %.1f", w.elapsedTime);

    float totalPointsLength = MeasureText(totalPoints, 42);
    float gameOverLength = MeasureText("Game Over!", 56);

    float gameOverY = (GetScreenHeight() - 56) / 2;
    float totalPointsY = gameOverY + 56;

    DrawText("Game Over", (GetScreenWidth() - gameOverLength) / 2, gameOverY, 56, BLACK);
    DrawText(totalPoints, (GetScreenWidth() - totalPointsLength) / 2, totalPointsY, 42, BLACK);

    Color c = VIOLET;

    if (pointInRect(GAME_OVER_BUTTON, GetMousePosition())) {
        c = RED;
    }

    DrawRectangleRec(GAME_OVER_BUTTON, c);
    DrawTextRec(alagard, "Restart", centerText(GAME_OVER_BUTTON, "Restart", 50), 50, 1, 0, WHITE);
}


void drawCircle(Ball b, Color c) {
    DrawCircle(b.position.x, b.position.y, b.radius, c);
}

void endGraphics() {
    UnloadFont(alagard);
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

Rectangle centerText(Rectangle rec, char* txt, int size) {
    float len = MeasureTextEx(alagard, txt, size, 1).x;
    Rectangle res = {
        .x = rec.x + rec.width/2 - len/2,
        .y = rec.y,
        .width = len,
        .height = rec.height
    };
    return res;
}
