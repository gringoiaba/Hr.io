#include "PlayerScore.h"
#include <stdio.h>

void insertScore(PlayerScore newScore, int index) {
    if (index >= HIGHSCORE_SIZE) {
        return;
    }
    if (newScore.score > scores[index].score) {
        PlayerScore old = scores[index];
        scores[index] = newScore;
        insertScore(old, index + 1);
    } else {
        insertScore(newScore, index + 1);
    }
}

void saveScore() {
    FILE *highscores = fopen("winner.bin", "wb");

    if (highscores) {
        fwrite(scores, sizeof(PlayerScore), HIGHSCORE_SIZE, highscores);
        fclose(highscores);
    }
}


void loadScore() {
    FILE *highscores = fopen("winner.bin", "rb");

    if (highscores) {
        fread(scores, sizeof(PlayerScore), HIGHSCORE_SIZE, highscores);
        fclose(highscores);
    }
}
