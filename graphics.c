#include "graphics.h"
#include "raylib.h"
#include "Structs/Vec2.h"
#include "Structs/Circle.h"
#include "Structs/World.h"
#include "Structs/Enemy.h"
#include "input.h"
#include <stdio.h>

#define newVector2(x, y) ((Vector2) {x, y})

Font alagard;
Camera2D cam;
int isRunning;

Camera2D getCam() {
    return cam;
}

void setIsRunning(int r) {
    isRunning = r;
}

// Initiates the main graphics of the game
void initGraphics() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hr.io"); // Sets the parameters of the game window
    SetTargetFPS(60); // Game fps

    isRunning = 1;

    alagard = LoadFont("res/alagard.png"); // Text font used

    cam = (Camera2D) { 0 };  // Creates the camera
    cam.offset = (Vector2) { SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f }; // Changes the center of the camera
    cam.zoom = 1.0f; // Camera zoom

    SetExitKey(0);
}

void drawWorld(World w) {

    BeginDrawing();

    ClearBackground(BLACK); // Set the background color

    // Run the program according to the game state
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
    case ASK_NAME:
        drawAskName(w);
        break;
    case HIGH_SCORE_SCREEN:
        drawHighScoreScreen(w);
        break;
    }

    DrawFPS(0, 30);

    EndDrawing();
}

// Draws the graphics of a playing game
void drawPlaying(World w, int showScore) {
    int i;

    cam.target = vec2ToVector2(w.player.position); // Sets the target of the camera to the player position
    cam.zoom = 1 + 2/w.player.radius;  // Sets the camera zoom

        BeginMode2D(cam);


            if (w.player.isAlive) { // If the player is alive...
                Color c = VIOLET; // Sets the player color to violet


                // Make poisoned balls flicker
                int time = (int)(w.player.poisonTimeRemaining * 3);
                if (time % 2 == 1) {
                    // "mix" the colors togehter

                    c = GetColor((ColorToInt(GREEN) + ColorToInt(c)) / 2);
                }

                drawCircle(w.player, c, w.player.name); // Draws the player
            }

            // Loop through the enemies and draws them
            for (i = 0; i < NUM_ENEMIES; i++) {
                if (w.enemies[i].ball.isAlive) {
                    Color c;

                    switch (w.enemies[i].elementalType) {
                    case EXPLOSIVE: // The explosive type color is orange
                        c = ORANGE;
                        break;
                    case POISONOUS: // The poisonous type is green
                        c = GREEN;
                        break;
                    case NONE:  // The normal type is red
                        c = RED;
                        break;
                    }

                    // Make poisoned balls flicker
                    int time = (int)(w.enemies[i].ball.poisonTimeRemaining * 3);
                    if (time % 2 == 1) {
                        // "mix" the colors togehter
                        c = GetColor((ColorToInt(GREEN) + ColorToInt(c)) / 2);
                    }

                    drawCircle(w.enemies[i].ball, c, w.enemies[i].ball.name);
                }
            }

            // Draws the food
            for (i = 0; i < NUM_FOOD; i++) {
                if (w.foods[i].isAlive) {
                    drawCircle(w.foods[i], YELLOW, "");
                }
            }

        EndMode2D();

    // Draws the player score
    if (showScore) {
        char mensagem[51];
        sprintf(mensagem, "Score: %.1f", w.elapsedTime);

        DrawTextEx(alagard, mensagem, (Vector2){0, 0}, 36, 1, WHITE);
    }
}

// Draws the game state of game over
void drawGameOver(World w) {
    drawPlaying(w, 0); // Draws the game in the background

    // Make the world a bit darker
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(DARKGRAY, 0.3));

    // Prints the final score
    char totalPoints[51];
    sprintf(totalPoints, "Your total score was %.1f", w.elapsedTime);

    // Draws the labels
    DrawTextRec(alagard, "Game Over", centerText(GAME_OVER_LABEL, "Game Over", 56), 56, 1, 0, WHITE);
    DrawTextRec(alagard, totalPoints, centerText(GAME_OVER_SCORE_LABEL, totalPoints, 42), 42, 1, 0, WHITE);

    Color restart = WHITE,
          menu = WHITE;

    // Makes the labels more interactive
    if (pointInRect(GAME_OVER_BUTTON, GetMousePosition())) {
        restart = BLACK;
    } else if (pointInRect(GAME_OVER_MENU_BUTTON, GetMousePosition())) {
          menu = BLACK;
    }

    DrawRectangleRec(GAME_OVER_BUTTON, restart);
    DrawTextRec(alagard, "Restart", centerText(GAME_OVER_BUTTON, "Restart", 51), 51, 1, 0, complementaryColor(restart));


    drawButton("Main Menu", GAME_OVER_MENU_BUTTON, menu, 51);
}

// Function that draws a circle and a circle's name
void drawCircle(Ball b, Color c, char* name) {
    DrawCircle(b.position.x, b.position.y, b.radius, c); // Draws the circle at its position

    Rectangle textPos = centerText(
        (Rectangle){
            b.position.x - b.radius,
            b.position.y,
            b.radius * 2,
            b.radius * 2
        },
        name,
        b.radius / 1.5f
    );

    // Draws the name in the center of the circle
    DrawTextRec(alagard, name, textPos, b.radius / 1.5f, 1, 1, complementaryColor(c));
}

// Ends the graphics
void endGraphics() {
    UnloadFont(alagard);
    CloseWindow();
}


int isGraphicsRunning() {
    return isRunning && !WindowShouldClose();
}

// Function that returns a Vector2 (vector of the raylib library) to a Vec2 (created by the game developers)
Vector2 vec2ToVector2(Vec2 v) {
    Vector2 res;

    res.x = v.x;
    res.y = v.y;

    return res;
}

// Function that receives a rectangle and a string and returns a new rectangle to center the string
Rectangle centerText(Rectangle rec, char* txt, int size) {
    Vector2 len = MeasureTextEx(alagard, txt, size, 1);

    // Creates the rectangle in with the text will be centered
    Rectangle res = {
        .x = rec.x + rec.width/2 - len.x/2,
        .y = rec.y,
        .width = len.x + 5, // A little extra for the last character
        .height = len.y
    };

    return res;
}

// Function that receives a color and returns its complementary color
Color complementaryColor(Color c) {
    return (Color) {
        .r = ~c.r,
        .g = ~c.g,
        .b = ~c.b,
        .a = 255
    };
}

// Draws the main menu
void drawMainMenu(World w) {

    drawPlaying(w, 0); // Makes the background as a playing game for aesthetics

    DrawTextRec(alagard, "H r . i o", centerText(MAIN_MENU_TITLE_LABEL, "H r . i o", 100), 100, 1, 0, WHITE); // Draws the game title

    drawLabel(w); // Draws the enemy labels

    // Sets the main menu button colors
    Color start = WHITE,
          load = WHITE,
          hiscore = WHITE,
          exit = WHITE;

    // Makes the buttons change color when the mouse is on it
    if (pointInRect(MAIN_MENU_START_BUTTON, GetMousePosition())) {
        start = BLACK;
    } else if (pointInRect(MAIN_MENU_LOAD_BUTTON, GetMousePosition())) {
          load = BLACK;
    } else if (pointInRect(MAIN_MENU_HISCORE_BUTTON, GetMousePosition())) {
          hiscore = BLACK;
    } else if (pointInRect(MAIN_MENU_EXIT_BUTTON, GetMousePosition())) {
          exit = RED;
    }

    // Draws all the buttons in the main menu
    drawButton("Start", MAIN_MENU_START_BUTTON, start, 51);
    drawButton("Load", MAIN_MENU_LOAD_BUTTON, load, 51);
    drawButton("High Scores", MAIN_MENU_HISCORE_BUTTON, hiscore, 51);
    drawButton("Exit", MAIN_MENU_EXIT_BUTTON, exit, 51);
}

// Function that draws a "button"
void drawButton(char* label, Rectangle rec, Color c, int fontSize) {
    // A button is a rectangle with centered text
    DrawRectangleRec(rec, c);
    DrawTextRec(alagard, label, centerText(rec, label, fontSize), fontSize, 1, 0, complementaryColor(c));
}

// Draws the pause menu
void drawPauseMenu(World w) {
    drawPlaying(w, 1);

    // Draws the message that the game is paused
    DrawTextRec(alagard, "Paused", centerText(PAUSE_MENU_LABEL, "Paused", 100), 100, 1, 0, WHITE);

    // Sets the pause buttons colors
    Color resume = WHITE,
          save = WHITE,
          exit = WHITE;

    // Makes the buttons change color when the mouse is on it
    if (pointInRect(PAUSE_MENU_RESUME_BUTTON, GetMousePosition())) {
        resume = BLACK;
    } else if (pointInRect(PAUSE_MENU_SAVE_BUTTON, GetMousePosition())) {
        save = BLACK;
    } else if (pointInRect(PAUSE_MENU_EXIT_BUTTON, GetMousePosition())) {
        exit = BLACK;
    }

    // Draws all the buttons in the main menu
    drawButton("Resume", PAUSE_MENU_RESUME_BUTTON, resume, 51);
    drawButton("Save", PAUSE_MENU_SAVE_BUTTON, save, 51);
    drawButton("Exit", PAUSE_MENU_EXIT_BUTTON, exit, 51);
}

// Draws the window when the user is asked a name
void drawAskName(World w) {
    Color c = DARKGRAY;
    Color buttonColor = RAYWHITE;

    // Makes the button change color when mouse is on it
    if (pointInRect(ASK_NAME_CONFIRM_BUTTON, GetMousePosition())) {
        buttonColor = BLACK;
    }

    // Prints the text asking the users name
    DrawTextRec(alagard, "What's your name?", centerText(ASK_NAME_LABEL, "What's your name?", 52), 52, 1, 1, complementaryColor(c));

    // Draws a rectangle in with the name will be written
    DrawRectangleRec(ASK_NAME_INPUT_BOX, c);
    DrawRectangleLinesEx(ASK_NAME_INPUT_BOX, 4, complementaryColor(c));

    // Prints the player name
    DrawTextEx(alagard, w.player.name, (Vector2){ ASK_NAME_INPUT_BOX.x + 4, ASK_NAME_INPUT_BOX.y }, 48, 1, complementaryColor(c));

    // Draws the confirm button
    drawButton("Confirm ", ASK_NAME_CONFIRM_BUTTON, buttonColor, 48);
}

// Function that draws the high score screen
void drawHighScoreScreen(World w) {
    int i;

    // Prints the message of high score
    DrawTextRec(
        alagard,
        "Highest scores of Hr.io:",
        centerText(HIGH_SCORE_LABEL, "Highest scores of Hr.io:", 32),
        32,
        1,
        0,
        WHITE
    );

    Color c = DARKGRAY;
    //Prints the all the high scores
    for (i = 0; i < HIGHSCORE_SIZE; i++) {
        if (getScores()[i].score <= 0) { // Only prints the score if its greater than zero
            break;
        }

        // Creates a rectangle to print the score
        Rectangle rec;
        rec.x = SCREEN_WIDTH / 2 - 500 / 2;
        rec.y = HIGH_SCORE_LABEL.y + (i+1) * 50;
        rec.height = 45;
        rec.width = 500;

        DrawRectangleRec(rec, c);

        char* txt = FormatText("%s: %g", getScores()[i].name, getScores()[i].score);

        // Draws the score in the rectangle
        DrawTextRec(
            alagard,
            txt,
            centerText(rec, txt, 32),
            32,
            1,
            0,
            complementaryColor(c)
        );

        c = complementaryColor(c);
    }

    // Makes the back button and checks if the mouse is on it to change color
    Color bt = BLACK;
    if (pointInRect(HIGH_SCORE_BACK_BUTTON, GetMousePosition())) {
        bt = RAYWHITE;
    }
    drawButton("Back", HIGH_SCORE_BACK_BUTTON, bt, 32);
}

// Draw the enemy labels
void drawLabel (World w) {
    // Draw Poisonous label
    DrawRectangle(25, 450, 30, 30, GREEN);
    DrawText("Poisonous ", 60, 455, 24, WHITE);

    // Draw Explosive label
    DrawRectangle(25, 500, 30, 30, ORANGE);
    DrawText("Explosive ", 60, 505, 24, WHITE);

    //Draw Normal label
    DrawRectangle(25, 550, 30, 30, RED);
    DrawText("Normal ", 60, 555, 24, WHITE);

}
