#pragma once
#include "Header.h"
#include <functional>
#include <iostream>
#include <windows.h>
#include <vector>
#include "time.h"
#include <fstream>
#include <conio.h>
#include <iomanip>
#include "Save.h"
#include "Bot.h"
using namespace std;

//Sacred.Name1 = "P1";

int _X, _Y;
int BEGIN = 1;
Point CurPa;
Point Last_Move_Point;
bool flag = true;
bool DebugMode = true;
bool VFXmode = true;
bool SFXmode = true;
int choiceSET = 0;
bool isInGame = false;

void gotoXY(int x, int y)
{
    
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void clearscreen()
{
    system("cls");
}
void displayMENU(int choice)
{
    gotoXY(10, 5);

    string menu[7] = {
       "START GAME PVP",
       "START GAME PVE",
       "INSTRUCTION",
       "ABOUT",
       "LOAD GAME",
       "SETTINGS",
       "EXIT"
    };
    int x = 52, y = 10;
    gotoXY(x, y - 1);

    cout << "----MENU----" << endl;
    for (int i = 0; i < 6; i++)
    {

        gotoXY(x, y + i);
        cout << menu[i] << endl;
        if (i == choice)
        {
            gotoXY(x - 2, y + i);
            cout << ">";
        }
    }
}
void displayABOUT()
{
    int x = 50, y = 10;
    gotoXY(54, 10);
    cout << "----ABOUT----\n";

    y++; gotoXY(x, y); cout << "Game: :))) " << endl;
    y++; gotoXY(x, y); cout << "Version: 1.0" << endl;
    y++; gotoXY(x, y); cout << "Author: Jon Snow 24120235" << endl;
    y++; gotoXY(x, y); cout << "Programming Language: C++" << endl;
    y++; gotoXY(x, y); cout << "Developed: 7/31/2025" << endl;
    y++; gotoXY(x, y); cout << "==============================" << endl;
    y++; gotoXY(x, y); cout << "This is a simple console game" << endl;
    y++; gotoXY(x, y); cout << "created for learning purposes." << endl;
    y++; gotoXY(x, y); cout << "==============================" << endl;
    while (true)
    {
        for (int i = 0; i < 16; i++)
        {
            SetColor(i, 0);
            escape_button(2, 1);
        }
        

        SetColor(4, 0);
        escape_button(2, 1);

        SetColor(15, 0);
        escape_button(2, 1);
        // Nếu có phím được nhấn
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'q' || key == 27)
            {
                Menu();
            }
            // nếu không phải d, l, q thì không làm gì => vòng lặp tiếp tục
        }
    }
}
#define LEFT 39
#define TOP 8

void DrawBoard(int pSize)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (0 << 4) | 7);
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    box0();

    for (int i = 0; i <= pSize - 1; i++)
    {
        for (int j = 0; j <= pSize - 1; j++)
        {
            gotoXY(LEFT, TOP + 2 * j);
            cout << u8"╠";

            //
            gotoXY(LEFT + 4 * i, TOP + 2 * j);
            cout << u8"╬══";
            gotoXY(LEFT + 4 * i, TOP);
            cout << u8"╦═══";
            gotoXY(LEFT + 4 * i + 4, TOP + 2 * j);
            cout << u8"╣";
            gotoXY(LEFT + 4 * (i)+4, TOP + 2 * j + 1);
            cout << u8"║ ";
            gotoXY(LEFT + 4 * (i), TOP + 2 * j + 1);
            cout << u8"║ ";
            //dong cuoi
            gotoXY(LEFT + 4 * i, TOP + 2 * j + 2);
            cout << u8"╬═══";
            gotoXY(LEFT + 4 * i + 4, TOP + 2 * j + 2);
            cout << u8"╣";
            gotoXY(LEFT + 4 * pSize, TOP);
            cout << u8"╗";
            gotoXY(LEFT + 4 * i, TOP + 2 * pSize);
            cout << u8"╩═══";
            //goc tren
            gotoXY(LEFT, TOP);
            cout << u8"╔";
            //goc duoi
            gotoXY(LEFT + 4 * pSize, TOP + 2 * pSize);
            cout << u8"╝";
            gotoXY(LEFT, TOP + 2 * pSize);
            cout << u8"╚";

        }
    }
    gotoXY(62, 1); cout << Sacred.curRound;
    string temp = (Sacred.isPVP) ? "PVP" : "PVE";
    gotoXY(52, 1); cout << temp;
    gotoXY(39, 3); cout << Sacred.Name1;
    gotoXY(70, 3); cout << Sacred.Name2;
    gotoXY(35, 4); cout << Sacred.P1;
    gotoXY(67, 4); cout << Sacred.P2;
    gotoXY(_X, _Y);
    /* int top = 1;
     for (int i = 0; i < pSize; i++)
     {
         for (int j = 0; j < pSize; j++)
         {
             gotoXY(i*4,2*j);  cout << u8"════";
         }
     }
     gotoXY(0, 0); cout << u8"╔";

     gotoXY(0, 1); cout << u8"║";*/
    drawCordinate();
}


void moveUp()
{
    CurPa.x = _X;
    CurPa.y = _Y;
    if (_Y - 2 >= Mother_Point_y)
        _Y -= 2;
    else
        _Y = Mother_Point_y + 2 * (BOARD_SIZE - 1);
    VFX_move();
    gotoXY(_X, _Y);
}
void moveDown()
{
    CurPa.x = _X;
    CurPa.y = _Y;
    if (_Y + 2 <= Mother_Point_y + 2 * (BOARD_SIZE - 1))
        _Y += 2;
    else
        _Y = Mother_Point_y;
    VFX_move();

    gotoXY(_X, _Y);
}
void moveLeft()
{
    CurPa.x = _X;
    CurPa.y = _Y;
    if (_X - 4 >= Mother_Point_x)
        _X -= 4;
    else
        _X = Mother_Point_x + 4 * (BOARD_SIZE - 1);
    VFX_move();

    gotoXY(_X, _Y);
}
void moveRight()
{
    CurPa.x = _X;
    CurPa.y = _Y;
    if (_X + 4 <= Mother_Point_x + 4 * (BOARD_SIZE - 1))
        _X += 4;
    else
        _X = Mother_Point_x;
    VFX_move();

    gotoXY(_X, _Y);
}
void printBoard(const vector<vector<int>>& board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[i].size(); j++)
        {
            char c = '.';
            if (board[i][j] == 1)cout << 1;
            else  if (board[i][j] == 2)cout << 2;
            else cout << 0;
        }
        cout << "\n";
    }

}
void resetBoard(GameRound& Sacred)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Sacred.board[i][j] = 0;

            //// Xoá ký tự trên màn hình tại ô (i, j)
            //int x = Mother_Point_x + j * 4;
            //int y = Mother_Point_y + i * 2;
            //gotoXY(x, y);
            //cout << "R";   // in khoảng trắng để xoá X/O cũ
        }
    }
}

void resetData()
{
    _X = Mother_Point_x;
    _Y = Mother_Point_y;
    resetBoard(Sacred);
    Sacred.isXTurn = true;
    Sacred.P1 = Sacred.P2 = 0;
    Sacred.cPointer = { _X,_Y };
    Sacred.chess_on_board = 0;
    Sacred.curRound = 1;
    Last_Move_Point.x = -1;
    Last_Move_Point.y = -1;;
    
}
// 
void updateRoundGame(int Winner)
{
    Sacred.curRound++;
    (Winner == 1) ? Sacred.P1++: Sacred.P2++;
    Sacred.isXTurn = true;
    Sacred.chess_on_board = 0;
    _X = Mother_Point_x;
    _Y = Mother_Point_y;
    Sacred.cPointer = { _X,_Y };
    resetBoard(Sacred);
    //Sleep(4000);
    BEGIN = 3;
    CurPa.x = -1;
    CurPa.y = -1;
    
    startGame();
    //Sleep(4000);
}
void recoverBoard()
{
    int countX = 0, countO = 0;
    //clearscreen();
    DrawBoard(BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (Sacred.board[i][j] != 0) {
                int x = Mother_Point_x + j * 4;
                int y = Mother_Point_y + i * 2;

                gotoXY(x, y);
                if (Sacred.board[i][j] == 1) {
                    SetColor(4, 0);
                    cout << "X";
                    countX++;
                }
                else {
                    SetColor(11, 0);
                    cout << "O";
                    countO++;
                }
            }
        }
    }
    if (Sacred.isXTurn)
        print_X_Bright(11, 11);
    else
        print_X_Dark(11, 11);
    SetColor(6, 0);
    square_cell(_X, _Y);
    if (Sacred.chess_on_board == 0) return;
    int col = (_X - Mother_Point_x) / 4;
    int row = (_Y - Mother_Point_y) / 2;
    if (Sacred.board[row][col] == 2) print_Target_color_order(_X, _Y, "O", 15);
    else if (Sacred.board[row][col] == 1) print_Target_color_order(_X, _Y, "X", 15);
    if (DebugMode)
    {
        SetColor(0, 4);
        gotoXY(_X, Mother_Point_y - 2); cout << col;
        gotoXY(Mother_Point_x - 4, _Y); cout << row;
        SetColor(15, 0);
        gotoXY(30, 25); cout << "(" << col << ", " << row << ")";

    }
    }
//void box1();
//void checkBoardHelper(vector<vector<int>>board, vector<int>& checkline, int x, int y)
//{
//    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) return;
//
//}
//int checkBoard(vector<vector<int>>board)
//{
//    // return 1 X win, 2 O win
//    int countX = 0, countY = 0;
//    // check ngang
//    for (int i = 0; i < BOARD_SIZE; i++)
//    {
//
//    }
//    return 0;
//    vector<int>checkline;
//
//}
int countInDirection(const vector<vector<int>>& board, int x, int y, int dx, int dy) {
    int n = board.size();
    int player = board[x][y];
    int count = 0;

    int nx = x + dx, ny = y + dy;
    while (nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] == player) {
        count++;
        nx += dx;
        ny += dy;
    }

    return count;
}
vector<Point> collectInDirection(const vector<vector<int>>& board, int x, int y, int dx, int dy) 
{
    int n = board.size();
    int player = board[x][y];
    vector<Point> result;

    int nx = x + dx, ny = y + dy;
    while (nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] == player) {
        result.push_back({ nx, ny });
        nx += dx;
        ny += dy;
    }

    return result;
}

int checkBoard(const vector<vector<int>>& board, vector<Point>& winningStreak) 
{
    int n = board.size();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (board[i][j] == 0) continue;
            int player = board[i][j];

            // Dọc
            if (i >= 4 || i <= n - 5) {
                int count = 1;
                vector<Point> temp = { {i, j} };
                if (i >= 4) {
                    auto up = collectInDirection(board, i, j, -1, 0);
                    count += up.size();
                    temp.insert(temp.end(), up.begin(), up.end());
                }
                if (i <= n - 5) {
                    auto down = collectInDirection(board, i, j, 1, 0);
                    count += down.size();
                    temp.insert(temp.end(), down.begin(), down.end());
                }
                if (count >= 5) {
                    winningStreak = temp;
                    return player;
                }
            }

            // Ngang
            if (j >= 4 || j <= n - 5) {
                int count = 1;
                vector<Point> temp = { {i, j} };
                if (j >= 4) {
                    auto left = collectInDirection(board, i, j, 0, -1);
                    count += left.size();
                    temp.insert(temp.end(), left.begin(), left.end());
                }
                if (j <= n - 5) {
                    auto right = collectInDirection(board, i, j, 0, 1);
                    count += right.size();
                    temp.insert(temp.end(), right.begin(), right.end());
                }
                if (count >= 5) {
                    winningStreak = temp;
                    return player;
                }
            }

            // Chéo chính
            if ((i >= 4 && j >= 4) || (i <= n - 5 && j <= n - 5)) {
                int count = 1;
                vector<Point> temp = { {i, j} };
                if (i >= 4 && j >= 4) {
                    auto upLeft = collectInDirection(board, i, j, -1, -1);
                    count += upLeft.size();
                    temp.insert(temp.end(), upLeft.begin(), upLeft.end());
                }
                if (i <= n - 5 && j <= n - 5) {
                    auto downRight = collectInDirection(board, i, j, 1, 1);
                    count += downRight.size();
                    temp.insert(temp.end(), downRight.begin(), downRight.end());
                }
                if (count >= 5) {
                    winningStreak = temp;
                    return player;
                }
            }

            // Chéo phụ
            if ((i >= 4 && j <= n - 5) || (i <= n - 5 && j >= 4)) {
                int count = 1;
                vector<Point> temp = { {i, j} };
                if (i >= 4 && j <= n - 5) {
                    auto upRight = collectInDirection(board, i, j, -1, 1);
                    count += upRight.size();
                    temp.insert(temp.end(), upRight.begin(), upRight.end());
                }
                if (i <= n - 5 && j >= 4) {
                    auto downLeft = collectInDirection(board, i, j, 1, -1);
                    count += downLeft.size();
                    temp.insert(temp.end(), downLeft.begin(), downLeft.end());
                }
                if (count >= 5) {
                    winningStreak = temp;
                    return player;
                }
            }
        }
    }

    return 0;
}

void visualFX(int loop_time, std::function<void()> func) 
{
    if (loop_time == 0) return;
    func();
    visualFX(loop_time - 1, func);
}

void drawLine(vector<Point> winningStreak, bool turn)
{
    bool flag = false;
    Point Last_Move_Point;
    for (Point &b : winningStreak)
    {
        
        if (turn)
        {
            if (flag) {
                SetColor(11, 0);
                square_cell(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
                gotoXY(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
                cout << u8"O";
            }
            SetColor(14, 0);
            square_cell(Mother_Point_x + b.y * 4, Mother_Point_y + b.x * 2);
            gotoXY(Mother_Point_x + b.y * 4, Mother_Point_y + b.x * 2);
            cout << u8"O";
            Sleep(100);
        }
        else
        {
            if (flag) {
                SetColor(4, 0);
                square_cell(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
                gotoXY(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
                cout << u8"X";
            }
            SetColor(14, 0);
            square_cell(Mother_Point_x + b.y * 4, Mother_Point_y + b.x * 2);
            gotoXY(Mother_Point_x + b.y * 4, Mother_Point_y + b.x * 2);

            cout << u8"X";
            Sleep(100);
        }
        Last_Move_Point = b;
        flag = true;
    }
    if (turn)
    {
        SetColor(11, 0);
        square_cell(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
        gotoXY(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
        cout << u8"o";

    }
    else
    {
        SetColor(4, 0);
        square_cell(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
        gotoXY(Mother_Point_x + Last_Move_Point.y * 4, Mother_Point_y + Last_Move_Point.x * 2);
        cout << u8"x";
    }

    Sleep(200);
}

void runGameCheck() {
    vector<Point> winningStreak;
    int result = checkBoard(Sacred.board, winningStreak);
    bool turn = Sacred.isXTurn;
    if (result != 0) {
        gotoXY(1, 7);
        for (Point& b : winningStreak) cout << b.x << " " << b.y << endl;
        /*drawLine(winningStreak, Sacred.isXTurn);
        drawLine(winningStreak, Sacred.isXTurn);
        drawLine(winningStreak, Sacred.isXTurn);*/

        //Sleep(50000);
        visualFX(3, [&]() { drawLine(winningStreak, Sacred.isXTurn); });
        updateRoundGame(result);
        Sleep(4000);
    }
    //if (result == 0)
    //{
    //    gotoXY(1, 7);
    //    for (Point& b : winningStreak)
    //        cout << b.x << " " << b.y << endl;
    //    Sleep(50000); // ngủ một lần thôi

    //}
}



void DrawMinion(int x, int y) {
    cout << u8"\033[48; 5; 15m   \033[38; 5; 15; 48; 5; 15m▄\033[38; 5; 248; 48; 5; 15m▄\033[38; 5; 240; 48; 5; 255m▄\033[38; 5; 145; 48; 5; 15m▄\033[38; 5; 248; 48; 5; 15m▄\033[38; 5; 236; 48; 5; 251m▄\033[38; 5; 235; 48; 5; 237m▄\033[38; 5; 232; 48; 5; 235m▄\033[38; 5; 247; 48; 5; 255m▄\033[38; 5; 238; 48; 5; 254m▄\033[38; 5; 236; 48; 5; 235m▄\033[38; 5; 236; 48; 5; 236m▄\033[38; 5; 239; 48; 5; 237m▄\033[38; 5; 250; 48; 5; 253m▄\033[38; 5; 251; 48; 5; 15m▄\033[38; 5; 7; 48; 5; 15m▄▄▄\033[38; 5; 251; 48; 5; 15m▄\033[38; 5; 255; 48; 5; 15m▄\033[38; 5; 15; 48; 5; 15m▄\033[m";
            cout << u8"   \033[48; 5; 15m  \033[38; 5; 15; 48; 5; 15m▄\033[48; 5; 15m \033[38; 5; 234; 48; 5; 236m▄\033[38; 5; 235; 48; 5; 235m▄\033[38; 5; 232; 48; 5; 234m▄\033[38; 5; 234; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 236m▄▄\033[38; 5; 232; 48; 5; 0m▄\033[48; 5; 234m \033[38; 5; 236; 48; 5; 235m▄\033[38; 5; 236; 48; 5; 236m▄▄\033[38; 5; 236; 48; 5; 237m▄\033[38; 5; 236; 48; 5; 239m▄▄\033[38; 5; 236; 48; 5; 236m▄▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 242; 48; 5; 239m▄\033[38; 5; 254; 48; 5; 253m▄\033[48; 5; 15m \033[m";
            cout << u8" \033[48; 5; 15m  \033[38; 5; 253; 48; 5; 255m▄\033[38; 5; 233; 48; 5; 248m▄\033[38; 5; 236; 48; 5; 237m▄\033[38; 5; 236; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 237m▄\033[38; 5; 236; 48; 5; 236m▄\033[48; 5; 236m \033[38; 5; 236; 48; 5; 236m▄▄▄▄\033[48; 5; 236m    \033[38; 5; 236; 48; 5; 236m▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 234; 48; 5; 235m▄\033[38; 5; 253; 48; 5; 239m▄\033[38; 5; 15; 48; 5; 254m▄\033[38; 5; 15; 48; 5; 15m▄▄\033[m";
            cout << u8" \033[38; 5; 255; 48; 5; 15m▄\033[38; 5; 247; 48; 5; 15m▄\033[38; 5; 243; 48; 5; 188m▄\033[38; 5; 232; 48; 5; 0m▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 236m▄▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 236m▄▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 232; 48; 5; 235m▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 236m▄\033[38; 5; 234; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 236m▄\033[48; 5; 236m  \033[38; 5; 236; 48; 5; 234m▄\033[38; 5; 236; 48; 5; 235m▄\033[38; 5; 235; 48; 5; 7m▄\033[38; 5; 236; 48; 5; 188m▄\033[38; 5; 245; 48; 5; 255m▄\033[38; 5; 255; 48; 5; 15m▄\033[m";
            cout << u8" \033[38; 5; 237; 48; 5; 247m▄\033[38; 5; 234; 48; 5; 235m▄\033[38; 5; 234; 48; 5; 232m▄\033[38; 5; 234; 48; 5; 234m▄\033[48; 5; 234m \033[38; 5; 235; 48; 5; 235m▄\033[38; 5; 234; 48; 5; 235m▄\033[38; 5; 232; 48; 5; 233m▄\033[38; 5; 235; 48; 5; 236m▄▄\033[38; 5; 235; 48; 5; 233m▄\033[38; 5; 238; 48; 5; 234m▄\033[38; 5; 236; 48; 5; 235m▄\033[38; 5; 235; 48; 5; 235m▄\033[38; 5; 137; 48; 5; 236m▄\033[38; 5; 233; 48; 5; 235m▄\033[38; 5; 235; 48; 5; 236m▄\033[38; 5; 236; 48; 5; 236m▄\033[48; 5; 236m  \033[38; 5; 241; 48; 5; 236m▄\033[38; 5; 242; 48; 5; 236m▄\033[38; 5; 241; 48; 5; 237m▄\033[38; 5; 238; 48; 5; 247m▄\033[m";
            cout << u8" \033[38; 5; 15; 48; 5; 255m▄\033[38; 5; 251; 48; 5; 8m▄\033[38; 5; 236; 48; 5; 234m▄\033[48; 5; 234m \033[38; 5; 233; 48; 5; 234m▄▄\033[38; 5; 0; 48; 5; 233m▄\033[38; 5; 233; 48; 5; 233m▄\033[38; 5; 234; 48; 5; 235m▄\033[38; 5; 137; 48; 5; 239m▄\033[38; 5; 232; 48; 5; 239m▄\033[38; 5; 102; 48; 5; 238m▄\033[38; 5; 137; 48; 5; 239m▄\033[38; 5; 180; 48; 5; 180m▄\033[38; 5; 180; 48; 5; 174m▄\033[38; 5; 138; 48; 5; 239m▄\033[38; 5; 234; 48; 5; 233m▄\033[38; 5; 234; 48; 5; 235m▄\033[38; 5; 237; 48; 5; 235m▄\033[38; 5; 236; 48; 5; 233m▄\033[38; 5; 233; 48; 5; 243m▄\033[38; 5; 243; 48; 5; 255m▄\033[38; 5; 254; 48; 5; 15m▄\033[38; 5; 15; 48; 5; 15m▄\033[m";
            cout << u8" \033[48; 5; 15m \033[38; 5; 15; 48; 5; 188m▄\033[38; 5; 188; 48; 5; 239m▄\033[38; 5; 0; 48; 5; 233m▄\033[38; 5; 238; 48; 5; 232m▄\033[38; 5; 234; 48; 5; 233m▄\033[38; 5; 238; 48; 5; 232m▄\033[38; 5; 236; 48; 5; 233m▄\033[38; 5; 174; 48; 5; 236m▄\033[38; 5; 180; 48; 5; 137m▄\033[38; 5; 180; 48; 5; 235m▄\033[38; 5; 224; 48; 5; 188m▄\033[38; 5; 217; 48; 5; 137m▄\033[38; 5; 223; 48; 5; 180m▄\033[38; 5; 223; 48; 5; 223m▄\033[38; 5; 95; 48; 5; 137m▄\033[38; 5; 233; 48; 5; 233m▄\033[38; 5; 236; 48; 5; 234m▄\033[38; 5; 243; 48; 5; 236m▄\033[38; 5; 8; 48; 5; 236m▄\033[38; 5; 8; 48; 5; 233m▄\033[38; 5; 255; 48; 5; 238m▄\033[38; 5; 15; 48; 5; 253m▄\033[38; 5; 15; 48; 5; 15m▄\033[m";
            cout << u8" \033[48; 5; 15m  \033[38; 5; 254; 48; 5; 188m▄\033[38; 5; 242; 48; 5; 0m▄\033[38; 5; 95; 48; 5; 174m▄\033[38; 5; 174; 48; 5; 137m▄\033[38; 5; 180; 48; 5; 180m▄\033[38; 5; 95; 48; 5; 138m▄\033[38; 5; 223; 48; 5; 223m▄▄\033[38; 5; 217; 48; 5; 223m▄\033[38; 5; 223; 48; 5; 223m▄▄▄▄\033[38; 5; 180; 48; 5; 173m▄\033[38; 5; 137; 48; 5; 239m▄\033[38; 5; 145; 48; 5; 252m▄\033[38; 5; 255; 48; 5; 255m▄\033[48; 5; 15m \033[38; 5; 15; 48; 5; 15m▄▄\033[48; 5; 15m  \033[m";
            cout << u8" \033[48; 5; 15m  \033[38; 5; 254; 48; 5; 15m▄\033[38; 5; 238; 48; 5; 15m▄\033[38; 5; 233; 48; 5; 235m▄\033[38; 5; 234; 48; 5; 240m▄\033[38; 5; 234; 48; 5; 95m▄\033[38; 5; 233; 48; 5; 234m▄\033[38; 5; 235; 48; 5; 180m▄\033[38; 5; 95; 48; 5; 223m▄\033[38; 5; 223; 48; 5; 217m▄\033[38; 5; 223; 48; 5; 180m▄\033[38; 5; 181; 48; 5; 180m▄\033[38; 5; 174; 48; 5; 180m▄\033[38; 5; 173; 48; 5; 180m▄\033[38; 5; 239; 48; 5; 174m▄\033[38; 5; 248; 48; 5; 95m▄\033[38; 5; 15; 48; 5; 247m▄\033[38; 5; 15; 48; 5; 255m▄\033[38; 5; 15; 48; 5; 15m▄\033[48; 5; 15m    \033[m";
            cout << u8" \033[48; 5; 15m \033[38; 5; 255; 48; 5; 253m▄\033[38; 5; 249; 48; 5; 242m▄\033[38; 5; 145; 48; 5; 235m▄\033[38; 5; 234; 48; 5; 235m▄▄\033[38; 5; 237; 48; 5; 234m▄\033[38; 5; 238; 48; 5; 234m▄\033[38; 5; 59; 48; 5; 235m▄\033[38; 5; 95; 48; 5; 95m▄\033[38; 5; 131; 48; 5; 138m▄\033[38; 5; 236; 48; 5; 174m▄\033[38; 5; 237; 48; 5; 180m▄\033[38; 5; 249; 48; 5; 137m▄\033[38; 5; 145; 48; 5; 239m▄\033[38; 5; 255; 48; 5; 145m▄\033[38; 5; 15; 48; 5; 255m▄\033[48; 5; 15m       \033[m";
            cout << u8" \033[48; 5; 15m   \033[38; 5; 15; 48; 5; 15m▄\033[38; 5; 59; 48; 5; 248m▄\033[38; 5; 248; 48; 5; 241m▄\033[38; 5; 188; 48; 5; 7m▄\033[38; 5; 253; 48; 5; 252m▄\033[38; 5; 253; 48; 5; 251m▄\033[38; 5; 252; 48; 5; 243m▄\033[38; 5; 242; 48; 5; 131m▄\033[38; 5; 95; 48; 5; 235m▄\033[38; 5; 238; 48; 5; 247m▄\033[38; 5; 238; 48; 5; 15m▄\033[38; 5; 255; 48; 5; 15m▄\033[38; 5; 15; 48; 5; 15m▄\033[48; 5; 15m        \033[m";
            cout << u8" \033[48; 5; 15m  \033[38; 5; 253; 48; 5; 15m▄\033[38; 5; 236; 48; 5; 15m▄\033[38; 5; 143; 48; 5; 238m▄\033[38; 5; 143; 48; 5; 95m▄\033[38; 5; 143; 48; 5; 243m▄\033[38; 5; 137; 48; 5; 138m▄\033[38; 5; 95; 48; 5; 252m▄\033[38; 5; 131; 48; 5; 253m▄\033[38; 5; 210; 48; 5; 145m▄\033[38; 5; 254; 48; 5; 250m▄\033[38; 5; 248; 48; 5; 243m▄\033[38; 5; 255; 48; 5; 248m▄\033[38; 5; 236; 48; 5; 242m▄\033[38; 5; 254; 48; 5; 255m▄\033[48; 5; 15m        \033[m";
            cout << u8" \033[38; 5; 15; 48; 5; 15m▄\033[38; 5; 250; 48; 5; 188m▄\033[38; 5; 237; 48; 5; 240m▄\033[38; 5; 239; 48; 5; 236m▄\033[38; 5; 238; 48; 5; 236m▄\033[38; 5; 238; 48; 5; 237m▄\033[38; 5; 237; 48; 5; 143m▄\033[38; 5; 143; 48; 5; 143m▄\033[38; 5; 101; 48; 5; 95m▄\033[38; 5; 242; 48; 5; 131m▄\033[38; 5; 167; 48; 5; 203m▄\033[38; 5; 210; 48; 5; 254m▄\033[38; 5; 255; 48; 5; 254m▄\033[38; 5; 247; 48; 5; 249m▄\033[38; 5; 252; 48; 5; 249m▄\033[38; 5; 239; 48; 5; 138m▄\033[38; 5; 253; 48; 5; 255m▄\033[48; 5; 15m     \033[38; 5; 15; 48; 5; 15m▄▄\033[m";
            cout << u8" \033[49; 38; 5; 255m▀\033[49; 38; 5; 238m▀\033[49; 38; 5; 236m▀\033[49; 38; 5; 237m▀\033[49; 38; 5; 240m▀▀\033[49; 38; 5; 237m▀\033[49; 38; 5; 143m▀\033[49; 38; 5; 241m▀\033[49; 38; 5; 243m▀\033[49; 38; 5; 241m▀\033[49; 38; 5; 174m▀\033[49; 38; 5; 254m▀\033[49; 38; 5; 247m▀\033[49; 38; 5; 245m▀\033[49; 38; 5; 236m▀\033[49; 38; 5; 253m▀\033[49; 38; 5; 15m▀▀▀▀▀▀▀\033[m";
        
}



void blinkLastMove(int x, int y, char symbol, int blinkCount = 3, int delayMs = 200) {
    for (int i = 0; i < blinkCount; i++) {
        // Xóa ký tự
        gotoXY(x, y);
        printf(" ");
        Sleep(delayMs);

        // Vẽ lại ký tự
        gotoXY(x, y);
        printf("%c", symbol);
        Sleep(delayMs);
    }
}


void VFX_move()
{
    // Khôi phục lại ô cũ
    if (CurPa.x >= 0 && CurPa.y >= 0)
    {
        square_cell_parent(CurPa.x, CurPa.y);

        int col = (CurPa.x - Mother_Point_x) / 4;
        int row = (CurPa.y - Mother_Point_y) / 2;
       /* cout << "Debug VFX: row=" << row
            << " col=" << col
            << " val=" << Sacred.board[row][col] << endl;*/


        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {

            int temp = Sacred.board[row][col];
            if(temp != 0)
            if (Last_Move_Point.x == CurPa.x && Last_Move_Point.y == CurPa.y)
                (temp == 1)? print_Target_color_order(CurPa.x, CurPa.y, "X", 15): print_Target_color_order(CurPa.x, CurPa.y, "O", 15);
            else 
                (temp == 1) ? print_Target_color_order(CurPa.x, CurPa.y, "X", 4) : print_Target_color_order(CurPa.x, CurPa.y, "O", 11);

            //if (Sacred.board[row][col] == 1) {
            //    print_Target_color_order(CurPa.x, CurPa.y, "X", 4);

            //   // gotoXY(CurPa.x, CurPa.y); cout<<"R";
            //}
            //else if (Sacred.board[row][col] == 2) {
            //    print_Target_color_order(CurPa.x, CurPa.y, "O", 11);
            //}
            //else {
            //    
            //}
            if (DebugMode)
            {
                SetColor(15, 0);
                gotoXY(CurPa.x, Mother_Point_y - 2); cout << col;
                gotoXY(Mother_Point_x - 4, CurPa.y); cout << row;
            }
            
        }
    }

    // Highlight ô mới
    SetColor(6, 0);
    square_cell(_X, _Y);
    int col = (_X - Mother_Point_x) / 4;
    int row = (_Y - Mother_Point_y) / 2;
    if (Sacred.board[row][col] == 1) {
        print_Target_color_order(_X, _Y, "X", 4); // X đỏ sáng
    }
    else if (Sacred.board[row][col] == 2) {
        print_Target_color_order(_X, _Y, "O", 11); // O xanh sáng
    }
    if (DebugMode)
    {
        SetColor(0, 4);
        gotoXY(_X, Mother_Point_y - 2); cout << col;
        gotoXY(Mother_Point_x - 4, _Y); cout << row;
        SetColor(15, 0);
        gotoXY(30, 25); cout << "(" << col << ", " << row << ")";

    }
    
}

void startGame()
{

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (0 << 4) | 7);
    //gotoXY(_X, _Y);
    //gotoXY(1, 1);
    /*if(DebugMode)
    cout <<"BEGIN: "<< BEGIN << endl;*/
    CurPa.x = -1;
    CurPa.y = -1;
    if (flag != Sacred.isPVP) {
        resetData();
        BEGIN = 1;
        flag = !flag;
    }
    if(BEGIN == 1)
        display_Enter_Name_Room();
    system("cls");
    DrawBoard(BOARD_SIZE);



    if (BEGIN == 2)
    {

        box1();
        char k = _getch();
        clearscreen();

        if (k == 'y')
        {
            /*for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    cout<< Sacred.board[i][j];
                }
            }*/
            recoverBoard();
        }
        else
        { 
            resetData();
            display_Enter_Name_Room();
            system("cls");
            DrawBoard(BOARD_SIZE);
            recoverBoard();
        }
        if (DebugMode)
        {
            SetColor(0, 4);
            gotoXY(_X, Mother_Point_y - 2); cout << 0;
            gotoXY(Mother_Point_x - 4, _Y); cout << 0;
        }
        
   
    }
    else if (BEGIN == 1) // bắt đầu chơi
    {

        Last_Move_Point.x = -1;
        Last_Move_Point.y = -1;
        BEGIN = 2;
        _X = Mother_Point_x, _Y = Mother_Point_y;
        gotoXY(_X, _Y);
        print_X_Bright(11, 11);
        print_O_Dark(91, 11);
        SetColor(6, 0);
        square_cell(_X, _Y);
        SetColor(6, 15);
        if (DebugMode)
        {
            SetColor(0, 4);
            gotoXY(_X, Mother_Point_y - 2); cout << 0;
            gotoXY(Mother_Point_x - 4, _Y); cout << 0;
        } 
    }
    else if (BEGIN == 3) // next round
    {
         BEGIN = 2;
         Last_Move_Point.x = -1;
         Last_Move_Point.y = -1;
         resetBoard(Sacred);
         //recoverBoard(Sacred);
        // _X = Mother_Point_x, _Y = Mother_Point_y;
       //  gotoXY(_X, _Y);
         SetColor(6, 0);
         square_cell(_X, _Y);
         CurPa.x = _X;
         CurPa.y = _Y;
         //gotoXY(1, 1);
         if (DebugMode)
         {
            // printBoard(Sacred.board);
             SetColor(0, 4);
             gotoXY(_X, Mother_Point_y - 2); cout << 0;
             gotoXY(Mother_Point_x - 4, _Y); cout << 0;
         }
    }
    else if (BEGIN == 4) // load game
    {
        
        BEGIN = 2;
        recoverBoard();
    

        Last_Move_Point.x = _X;
        Last_Move_Point.y = _Y;
     
        /*gotoXY(_X, _Y);
        int temp = Sacred.board[(_Y - Mother_Point_y) / 2][(_X - Mother_Point_x) / 4];
        gotoXY(_X, _Y);
        if (temp == 1)
            print_Target_color_order(_X, _Y, "X", 15);
        else if (temp == 2)
            print_Target_color_order(_X, _Y, "O", 15);*/

    }

    while (true) {
        gotoXY(1, 1);
        if (DebugMode) printBoard(Sacred.board);
        print_O_Dark(91, 11);
        print_X_Dark(11, 11);
        if (Sacred.isXTurn)
        {
            print_X_Bright(11, 11);
            print_X_Dark(11, 11);
            print_X_Bright(11, 11);

        }
        else
        {
            print_O_Bright(91, 11);
            print_O_Dark(91, 11);
            print_O_Bright(91, 11);

        }
        //startGamePVE();
        if(!Sacred.isPVP) startGamePVE_2();
        gotoXY(_X, _Y);

        if (_kbhit()) 
        {
            char key = _getch();
            int col = (_X - Mother_Point_x) / 4;
            int row = (_Y - Mother_Point_y) / 2;
            if (key == 'q' || key == 'Q') {
                // return;
                flag = Sacred.isPVP;
                isInGame = false;
                BEGIN = 2;
                Menu();

            }
            else if (key == 13 && Sacred.board[row][col] == 0) {
                gotoXY(0, 25);
                

                if(DebugMode) cout << (Last_Move_Point.x - Mother_Point_x) / 4 << " " << (Last_Move_Point.y - Mother_Point_y) / 2;
               //Sacred.isNewBoard = false; ////////////////////////////
               if (Last_Move_Point.x == -1 && Last_Move_Point.y == -1)
                //if (Sacred.isNewBoard)
                {
                    SetColor(15, 0);
                    print_Step(_X, _Y, "X");
                    Sacred.board[row][col] = 1;
                    Last_Move_Point.x = _X;
                    Last_Move_Point.y = _Y;
                    Sacred.isXTurn = false;
                    Sacred.isNewBoard = false;
                }
                else
                {
                  // cout << "CCCCCCCCCCCCCC";

                    int temp = Sacred.board[(Last_Move_Point.y - Mother_Point_y) / 2][(Last_Move_Point.x - Mother_Point_x) / 4];
                    gotoXY(Last_Move_Point.x, Last_Move_Point.y);
                    if (temp == 1)
                        print_Target_color_order(Last_Move_Point.x, Last_Move_Point.y, "X", 4);
                    else if (temp == 2)
                        print_Target_color_order(Last_Move_Point.x, Last_Move_Point.y, "O", 11);
                    if (!Sacred.isXTurn)
                    {
                        /*gotoXY(Last_Move_Point.x, Last_Move_Point.y);
                        SetColor(4, 0);
                        printf("X");*/
                        Sacred.board[row][col] = 2;
                        print_Step(_X, _Y, "O");
                        Sacred.isXTurn = true;
                    }
                    else
                    {
                        /*gotoXY(Last_Move_Point.x, Last_Move_Point.y);
                        SetColor(11, 0);
                        printf("O");*/
                        Sacred.board[row][col] = 1;
                        print_Step(_X, _Y, "X");
                        for (int i = 0; i < 9; i++)
                        {
                            gotoXY(93, i); cout << "                           ";

                        }
                        Sacred.isXTurn = false;

                    }
                    Last_Move_Point.x = _X;
                    Last_Move_Point.y = _Y;
                }
                Sacred.lastMove = { _X,_Y };
                Sacred.chess_on_board++;
                runGameCheck();
                gotoXY(_X, _Y);
                fflush(stdout);
            }
            else if (key == 'w') moveUp();
            else if (key == 's') moveDown();
            else if (key == 'a') moveLeft();
            else if (key == 'd') moveRight();
            else if (key == 'p') {
               // DrawSquirtle(75, 1);
                //Character_1(95, 1);
                gotoXY(_X, _Y);
            }
            else if (key == 'l' || key == 'L') {
                saveGame();
                clearscreen();
                recoverBoard();
            }
            else if (key == 32)
            {
                pauseMenu();
            }
        }
        gotoXY(_X, _Y);   
    }
}




// helo



int choice = 0;

void Menu()
{
    system("cls");
    char key;
    while (true)
    {
        system("cls");
        SetColor(15, 0);
        displayMENU(choice);
        key = _getch();
        if (key == 'w' || key == 'W')
            choice = (choice - 1 + 6) % 6;
        else if (key == 's' || key == 'S')
            choice = (choice + 1) % 6;
        else if (key == 13)
        {
            system("cls");
            switch (choice)
            {
            case 0:  isInGame = true;  Sacred.isPVP = true; startGame(); break;
            case 1:  isInGame = true;  Sacred.isPVP = false;  startGame(); break;
            case 2: cout << "Instructions...\n"; break;
            case 3: displayABOUT(); break;
            case 4: LoadGame();
                /*for (string a : savedGames)
                    cout << a << endl;*/
                break;
            case 5: 
                choiceSET = 0;
                SETTING(); break;
            case 6:
                cout << "Cam on da choi! Tam biet!\n"; break;
            }
             system("pause");
        }
    }
}
//void SETTING()
//{
//    DebugMode = !DebugMode;
//}
void displaySetting(int choice)
{
    //int x = 55, y = 2;
    int x = 41, y = 12;
    gotoXY(x, y);         cout << u8R"(╔═══════════════════════════════════╗)";
    for (int i = 1; i < 5; i++)
    {
        gotoXY(x, y + i); cout << u8R"(║                                   ║)";
    }
    gotoXY(x, y + 5);     cout << u8R"(╚═══════════════════════════════════╝)";
    gotoXY(x + 10 - 2, choice + y + 1); cout << ">";
   /* gotoXY(x, y);
    cout << "SETTING";*/
    gotoXY(x + 10, y + 1); cout << u8"SFX: (";
    gotoXY(x + 6 + 10, y + 1);
    if (SFXmode) cout << "on)";
    else cout << "off)";
    gotoXY(x + 10, y + 2); cout << "VFX: (";
    gotoXY(x + 6 + 10, y + 2);
    if (VFXmode) cout << "on)";
    else cout << "off)";
    gotoXY(x + 10, y + 3); cout << "Debug Mode: (";
    gotoXY(x + 10 + 13, y + 3);
    if (DebugMode) cout << "on)";
    else cout << "off)";
    //gotoXY(x, y + 2);
}
//void SETTING()
//{
//    int choice;
//
//    DebugMode = !DebugMode;
//}


void SETTING()
{
    system("cls");

    char key;
    while (true)
    {
        system("cls");
        SetColor(15, 0);
        displaySetting(choiceSET);
        key = _getch();
        if (key == 'w' || key == 'W')
            choiceSET = (choiceSET - 1 + 4) % 4;
        else if (key == 's' || key == 'S')
            choiceSET = (choiceSET + 1) % 4;
        else if (key == 13)
        {
            system("cls");
            switch (choiceSET)
            {
            case 0: SFXmode = !SFXmode;  break;
            case 1: VFXmode = !VFXmode; break;
            case 2: DebugMode = !DebugMode; break;
            case 3: cout << "tieng viet"; break;
            }
            // system("pause");
        }
        else if (key == 'q')
        {
            if (isInGame) return;
            else Menu();
        }
    }
}
void displayPauseMENU(int choice)
{
    int x = 41, y = 12;
    gotoXY(x, y);         cout << u8R"(╔═══════════════════════════════════╗)";
    for (int i = 1; i < 7; i++)
    {
        gotoXY(x, y + i); cout << u8R"(║                                   ║)";
    }
    gotoXY(x, y + 7);     cout << u8R"(╚═══════════════════════════════════╝)";
    string menu[6] = {
        "continue", "Instruction", "Setting", "Load Game", "Save Game", "Escape"
    };
    
    for (int i = 0; i < 6; i++)
    {
        gotoXY(x + 15, y + 1 + i); cout << menu[i];
        /*if (choice == i) {
            gotoXY(x + 7, y + 1 + i); cout << ">";
        }*/
    }
    gotoXY(x + 13, y + 1 + choice); cout << ">";

}
void pauseMenu()
{
    int choice = 0;
    char key;
    int x = 36, y = 12;

    while (true)
    {
        //system("cls");
        SetColor(15, 0);
        displayPauseMENU(choice);
        key = _getch();
        if (key == 'w' || key == 'W')
            choice = (choice - 1 + 6) % 6;
        else if (key == 's' || key == 'S')
            choice = (choice + 1) % 6;
        else if (key == 13)
        {
            //system("cls");
            switch (choice)
            {
            case 0: system("cls"); recoverBoard();  return;
            case 1: VFXmode = !VFXmode; break;
            case 2: SETTING(); break;
            case 3: cout << "tieng viet"; break;
            case 4:  
                saveGame();
                clearscreen();
                recoverBoard(); 
                break;
            case 5: Menu(); break;
            }
            // system("pause");
        }
        else if (key == 'q')
        {
            system("cls"); recoverBoard();  return;
        }
    }
}