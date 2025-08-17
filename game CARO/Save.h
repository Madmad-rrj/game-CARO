#pragma once
#include "Header.h"
#include <string>
#ifndef SAVE_H
#define SAVE_H 
using namespace std;
extern GameRound Sacred;

void saveGame();
void saveToBoard(const string& fileName);
void readBoard(string fileName);
void readSaveFolder(vector<string>& savedGames);
void displayLoadGame(int choice, bool isDel);
void LoadGame();
void deleteSavedFile(const string& fileName);

#endif