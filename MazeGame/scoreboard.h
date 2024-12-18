#ifndef SCOREBOARD_H
#define SCOREBOARD_H

class Scoreboard
{
public:
    static void SaveBestScores();
    static void LoadBestScores();
    static void UpdateBestScores(int difficulty, float time);

    static float bestTimes[3][5];
};

#endif
