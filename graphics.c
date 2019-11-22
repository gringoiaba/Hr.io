#include "graphics.h"
#include "raylib.h"
#include "Structs/Vec2.h"
#include "Structs/Circle.h"
#include "Structs/World.h"
#include "Structs/Enemy.h"
#include <stdio.h>
#include "input.h"

#define newVector2(x, y) ((Vector2) {x, y})

Font alagard;

void initGraphics() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hr.io");
    SetTargetFPS(60);

    isRunning = 1;

    alagard = LoadFont("res/alagard.png");

    cam = (Camera2D) { 0 };
    cam.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    cam.zoom = 1.0f;

    SetExitKey(0);
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
    case MAIN_MENU:
        drawMainMenu(w);
        break;
    case PAUSE_MENU:
        drawPauseMenu(w);
        break;
    }

    DrawFPS(0, 0);

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

    DrawTextRec(alagard, "Game Over", centerText(GAME_OVER_LABEL, "Game Over", 56), 56, 1, 0, BLACK);
    DrawTextRec(alagard, totalPoints, centerText(GAME_OVER_SCORE_LABEL, totalPoints, 42), 42, 1, 0, BLACK);

    Color restart = BLACK,
          menu = BLACK;

    if (pointInRect(GAME_OVER_BUTTON, GetMousePosition())) {
        restart = WHITE;
    } else if (pointInRect(GAME_OVER_MENU_BUTTON, GetMousePosition())) {
          menu = WHITE;
    }

    DrawRectangleRec(GAME_OVER_BUTTON, restart);
    DrawTextRec(alagard, "Restart", centerText(GAME_OVER_BUTTON, "Restart", 51), 51, 1, 0, complementaryColor(restart));


    drawButton("Main Menu", GAME_OVER_MENU_BUTTON, menu, 51);
}


void drawCircle(Ball b, Color c) {
    DrawCircle(b.position.x, b.position.y, b.radius, c);
}

void endGraphics() {
    UnloadFont(alagard);
    CloseWindow();
}

int isGraphicsRunning() {
    return isRunning;
}

Vector2 vec2ToVector2(Vec2 v) {
    Vector2 res;

    res.x = v.x;
    res.y = v.y;

    return res;
}

Rectangle centerText(Rectangle rec, char* txt, int size) {
    Vector2 len = MeasureTextEx(alagard, txt, size, 1);

    Rectangle res = {
        .x = rec.x + rec.width/2 - len.x/2,
        .y = rec.y,
        .width = len.x,
        .height = len.y
    };

    return res;
}

Color complementaryColor(Color c) {
    return (Color) {
        .r = ~c.r,
        .g = ~c.g,
        .b = ~c.b,
        .a = 255
    };
}

void drawMainMenu(World w) {

    drawPlaying(w, 0);

    DrawTextRec(alagard, "H r . i o", centerText(MAIN_MENU_TITLE_LABEL, "H r . i o", 100), 100, 1, 0, BLACK);

    Color start = BLACK,
          load = BLACK,
          hiscore = BLACK,
          exit = BLACK;

    if (pointInRect(MAIN_MENU_START_BUTTON, GetMousePosition())) {
        start = WHITE;
    } else if (pointInRect(MAIN_MENU_LOAD_BUTTON, GetMousePosition())) {
          load = WHITE;
    } else if (pointInRect(MAIN_MENU_HISCORE_BUTTON, GetMousePosition())) {
          hiscore = WHITE;
    } else if (pointInRect(MAIN_MENU_EXIT_BUTTON, GetMousePosition())) {
          exit = RED;
    }

    drawButton("Start", MAIN_MENU_START_BUTTON, start, 51);

    // HACK: Raylib doesn't like 4-length strings for some reason????
    // Might need to fix this in the raylib code itself
    drawButton("Load ", MAIN_MENU_LOAD_BUTTON, load, 51);

    drawButton("High Scores", MAIN_MENU_HISCORE_BUTTON, hiscore, 51);
    drawButton("Exit", MAIN_MENU_EXIT_BUTTON, exit, 51);
}

void drawButton(char* label, Rectangle rec, Color c, int fontSize) {
    DrawRectangleRec(rec, c);
    DrawTextRec(alagard, label, centerText(rec, label, fontSize), fontSize, 1, 0, complementaryColor(c));
}

void drawPauseMenu(World w) {
    drawPlaying(w, 1);

    DrawTextRec(alagard, "Paused", centerText(PAUSE_MENU_LABEL, "Paused", 100), 100, 1, 0, BLACK);

    Color resume = BLACK,
          save = BLACK,
          exit = BLACK;

    if (pointInRect(PAUSE_MENU_RESUME_BUTTON, GetMousePosition())) {
        resume = WHITE;
    } else if (pointInRect(PAUSE_MENU_SAVE_BUTTON, GetMousePosition())) {
        save = WHITE;
    } else if (pointInRect(PAUSE_MENU_EXIT_BUTTON, GetMousePosition())) {
        exit = WHITE;
    }

    drawButton("Resume", PAUSE_MENU_RESUME_BUTTON, resume, 51);
    // HACK: Raylib doesn't like 4-length strings for some reason????
    // Might need to fix this in the raylib code itself
    drawButton("Save ", PAUSE_MENU_SAVE_BUTTON, save, 51);
    drawButton("Exit", PAUSE_MENU_EXIT_BUTTON, exit, 51);
}
