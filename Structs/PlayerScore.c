#include "PlayerScore.h"

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
