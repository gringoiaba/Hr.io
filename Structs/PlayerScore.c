#include "PlayerScore.h"
#include <stdio.h>

PlayerScore scores[HIGHSCORE_SIZE];
PlayerScore* getScores() {
    return scores;
}

// Inserts a score in a sorted way, so that new scores
// get ordered or discarded accordingly
void insertScore(PlayerScore newScore, int index) {
    // If we are trying to insert a score
    // outside the array, stop it
    if (index >= HIGHSCORE_SIZE) {
        return;
    }

    // If the new score is better than the index we are trying to
    // insert, put the new score here, and try to insert the old scor
    // in the next position of the array
    if (newScore.score > scores[index].score) {
        PlayerScore old = scores[index];
        scores[index] = newScore;
        insertScore(old, index + 1);

    // If the new score is NOT better, try to insert it into the next position
    } else {
        insertScore(newScore, index + 1);
    }
}

// Saves all the scores
void saveScore() {
    FILE *highscores = fopen("winner.bin", "wb");

    if (highscores) {
        fwrite(scores, sizeof(PlayerScore), HIGHSCORE_SIZE, highscores);
        fclose(highscores);
    }
}

// Load all the scores
void loadScore() {
    FILE *highscores = fopen("winner.bin", "rb");

    if (highscores) {
        fread(scores, sizeof(PlayerScore), HIGHSCORE_SIZE, highscores);
        fclose(highscores);
    }
}
