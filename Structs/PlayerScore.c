#include "PlayerScore.h"

void insertScore(PlayerScore *scores, PlayerScore newScore, int index) {
    if (index >= HIGHSCORE_SIZE) {
        return;
    }
    if (newScore.score > scores[index].score) {
        PlayerScore old = scores[index];
        scores[index] = newScore;
        insertScore(scores, old, index + 1);
    } else {
        insertScore(scores, newScore, index + 1);
    }
}


void printScores(PlayerScore *scores) {
    int i;
    for (i = 0; i < HIGHSCORE_SIZE; i++) {
        //if (scores[i].score > 0) {
            printf("%d %s: %f\n", i, scores[i].name, scores[i].score);

    }
}
