#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Structs/World.h"
#include "Structs/Vec2.h"
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define GAME_OVER_LABEL ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2, \
                                      .y = SCREEN_HEIGHT/2 - 50,   \
                                      .width = 300,                \
                                      .height = 50})

#define GAME_OVER_SCORE_LABEL ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,                          \
                                            .y = GAME_OVER_LABEL.y + GAME_OVER_LABEL.height,      \
                                            .width = 300,                                         \
                                            .height = 50})

#define GAME_OVER_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,                                  \
                                       .y = GAME_OVER_SCORE_LABEL.y + GAME_OVER_SCORE_LABEL.height,  \
                                       .width = 300,                                                 \
                                       .height = 50})

#define GAME_OVER_MENU_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,                            \
                                            .y = GAME_OVER_BUTTON.y + GAME_OVER_BUTTON.height + 10, \
                                            .width = 300,                                           \
                                            .height = 50})

#define MAIN_MENU_TITLE_LABEL ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,  \
                                            .y = 50,                      \
                                            .width = 300,                 \
                                            .height = 50})

#define MAIN_MENU_START_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,       \
                                            .y = MAIN_MENU_TITLE_LABEL.y + 150, \
                                            .width = 300,                       \
                                            .height = 50})

#define MAIN_MENU_LOAD_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,       \
                                            .y = MAIN_MENU_START_BUTTON.y + 75, \
                                            .width = 300,                       \
                                            .height = 50})

#define MAIN_MENU_HISCORE_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,         \
                                               .y = MAIN_MENU_LOAD_BUTTON.y + 75, \
                                               .width = 300,                        \
                                               .height = 50})

#define MAIN_MENU_EXIT_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,         \
                                            .y = MAIN_MENU_HISCORE_BUTTON.y + 75, \
                                            .width = 300,                        \
                                            .height = 50})

#define PAUSE_MENU_LABEL ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,         \
                                       .y = 50, \
                                       .width = 300,                        \
                                       .height = 50})

#define PAUSE_MENU_RESUME_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,         \
                                               .y = PAUSE_MENU_LABEL.y + 150, \
                                               .width = 300,                        \
                                               .height = 50})

#define PAUSE_MENU_SAVE_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,         \
                                             .y = PAUSE_MENU_RESUME_BUTTON.y + 75, \
                                             .width = 300,                        \
                                             .height = 50})

#define PAUSE_MENU_EXIT_BUTTON ((Rectangle) {.x = SCREEN_WIDTH/2 - 300/2,         \
                                               .y = PAUSE_MENU_SAVE_BUTTON.y + 75, \
                                               .width = 300,                        \
                                               .height = 50})

Camera2D cam;
int isRunning;

void initGraphics();
void drawWorld(World);
void endGraphics();
int isGraphicsRunning();
Vector2 vec2ToVector2(Vec2);
void drawCircle(Ball, Color);
void drawPlaying(World, int);
void drawGameOver(World);
Rectangle centerText(Rectangle, char*, int);
Color complementaryColor(Color);
void drawMainMenu(World);
void drawButton(char*, Rectangle, Color, int);
void drawPauseMenu(World);

#endif // GRAPHICS_H
