#pragma once
#include "Header.h"
#include "Save.h"
struct candidate
{
    Point cord;
    int streak;
    int status;
    vector<Point>Winningstreak;
};
void startGamePVE();
bool checkBoardPVE(int mode, const vector<vector<int>>& board, int streak, vector<candidate>& candidates);
Point randomPoint();
void startGamePVE_2();
void getDirection(int status, int& dx, int& dy);
void printCandidates(const vector<candidate>& candidates);