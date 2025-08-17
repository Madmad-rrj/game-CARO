#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <functional>

#include <conio.h>
using namespace std;
#define BOARD_SIZE 10
#define Mother_Point_x 41
#define Mother_Point_y 9
struct Point
{
    int x, y;
};
struct GameRound
{
    bool isXTurn;
    vector<vector<int>> board;
    int P1, P2;
    int curRound;
    string Name1, Name2;
    Point CurPoint;
    int FLAG;
    bool isNewBoard;
    GameRound() 
    {
        board = vector<vector<int>>(BOARD_SIZE, vector<int>(BOARD_SIZE, 0));
        isXTurn = true;
        P1 = P2 = 0;
        curRound = 1;
        Name1 = "P1";
        Name2 = "P2";
        CurPoint.x = Mother_Point_x;
        CurPoint.y = Mother_Point_y;
        FLAG = 0;
        isNewBoard = true;
    }
};
extern GameRound Sacred;

#include "Save.h"

void gotoXY(int x, int y);
void displayMENU(int choice);
void displayABOUT();
void DrawBoard(int pSize);
void moveUp();
void moveLeft();
void moveRight();
void printBoard(const vector<vector<int>>& board);
void recoverBoard();
void startGame();
void Menu();
void resetData();
void resetBoard();
int checkBoard(const vector<vector<int>>& board, vector<Point>& winningStreak);
void visualFX(int loop_time, std::function<void()> func);

void runGameCheck();
void box0();
void DrawBoard(int pSize);
void drawLine(vector<Point> winningStreak, bool turn);
void square_cell(int x, int y);
void frameListGame(int numberOfFile);
void delete_button(int x, int y);
void load_button(int x, int y);
void No_file_found();
void print_Step(int x, int y, string target);
void print_X_Dark(int x, int y);
void print_X_Bright(int x, int y);
void print_O_Bright(int x, int y);

void print_O_Dark(int x, int y);
void square_cell_parent(int x, int y);
void VFX_move();
void box1();
void SetColor(int mauchu, int mauBg);
void donothing();
void enter_fileName_box();
void print_Target_color_order(int x, int y, string target, int color);

void Character_1(int x, int y);
void Character_2(int x, int y);


