#ifndef STRUCTS_PLAYER_H
#define STRUCTS_PLAYER_H

#define HIGHSCORE_SIZE 10

#define NAME_SIZE (50 + 1)

// Structure that saves scores of a player
typedef struct {
    char name[NAME_SIZE]; // Contains a name of the user
    float score; // Score of the playthrough
} PlayerScore;

// Global high score tracker
PlayerScore* getScores();

void insertScore(PlayerScore, int);
void loadScore();
void saveScore();

#endif // STRUCTS_PLAYER_H
