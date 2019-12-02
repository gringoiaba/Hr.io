#ifndef STRUCTS_PLAYER_H
#define STRUCTS_PLAYER_H

#define HIGHSCORE_SIZE 10

#define NAME_SIZE (50 + 1)

typedef struct {
    char name[NAME_SIZE];
    float score;
} PlayerScore;

// Global highscore tracker
PlayerScore scores[HIGHSCORE_SIZE];

void insertScore(PlayerScore, int);
void loadScore();
void saveScore();

#endif // STRUCTS_PLAYER_H
