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
Point Parent;
bool flag = true;
bool DebugMode = true;
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
    Sacred.CurPoint = { _X,_Y };
    Sacred.chess_on_board = 0;
    Sacred.curRound = 1;
    Parent.x = -1;
    Parent.y = -1;;
}
void updateRoundGame(int Winner)
{
    Sacred.curRound++;
    (Winner == 1) ? Sacred.P1++: Sacred.P2++;
    Sacred.isXTurn = true;
    Sacred.chess_on_board = 0;
    _X = Mother_Point_x;
    _Y = Mother_Point_y;
    Sacred.CurPoint = { _X,_Y };
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
    square_cell(Sacred.CurPoint.x, Sacred.CurPoint.y);
    if (Sacred.chess_on_board == 0) return;
    int col = (Sacred.CurPoint.x - Mother_Point_x) / 4;
    int row = (Sacred.CurPoint.y - Mother_Point_y) / 2;
    if (Sacred.board[row][col] == 2) print_Target_color_order(Sacred.CurPoint.x, Sacred.CurPoint.y, "O", 15);
    else if (Sacred.board[row][col] == 1) print_Target_color_order(Sacred.CurPoint.x, Sacred.CurPoint.y, "X", 15);
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
    Point parent;
    for (Point &b : winningStreak)
    {
        
        if (turn)
        {
            if (flag) {
                SetColor(11, 0);
                square_cell(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
                gotoXY(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
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
                square_cell(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
                gotoXY(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
                cout << u8"X";
            }
            SetColor(14, 0);
            square_cell(Mother_Point_x + b.y * 4, Mother_Point_y + b.x * 2);
            gotoXY(Mother_Point_x + b.y * 4, Mother_Point_y + b.x * 2);

            cout << u8"X";
            Sleep(100);
        }
        parent = b;
        flag = true;
    }
    if (turn)
    {
        SetColor(11, 0);
        square_cell(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
        gotoXY(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
        cout << u8"o";

    }
    else
    {
        SetColor(4, 0);
        square_cell(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
        gotoXY(Mother_Point_x + parent.y * 4, Mother_Point_y + parent.x * 2);
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

//void startGame(GameRound& Sacred)
//{
//    Point curPoint = { -1, -1 };
//    Point Parent = { -1, -1 };
//    bool blinkState = false;
//    bool firstMove = true;
//    system("cls");
//    DrawBoard(BOARD_SIZE, Sacred);
//    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    SetConsoleTextAttribute(hStdOut, (0 << 4) | 7);
//    //gotoXY(_X, _Y);
//
//    if (BEGIN == 2)
//    {
//        box1();
//        char k = _getch();
//        clearscreen();
//
//        if (k == 'y')
//        {
//            /*for (int i = 0; i < BOARD_SIZE; i++) {
//                for (int j = 0; j < BOARD_SIZE; j++) {
//                    cout<< Sacred.board[i][j];
//                }
//            }*/
//            recoverBoard(Sacred);
//        }
//        else
//        {
//            resetData(Sacred);
//            recoverBoard(Sacred);
//        }
//    }
//    else if (BEGIN == 1)
//    {
//        BEGIN = 2;
//        _X = Mother_Point_x, _Y = Mother_Point_y;
//        gotoXY(_X, _Y);
//    }
//    else
//        recoverBoard(Sacred);
//
//    while (true) {
//        // --- VFX nhấp nháy ---
//        if (curPoint.x != -1 && curPoint.y != -1) {
//            gotoXY(curPoint.x, curPoint.y);
//            if (blinkState)
//                SetColor(15, 0);
//            else
//                if (Sacred.isXTurn)
//                    SetColor(11, 0);
//                else
//                    SetColor(4, 0);
//
//            char ch = Sacred.board[(curPoint.y - Mother_Point_y) / 2]
//                [(curPoint.x - Mother_Point_x) / 4] == 1 ? 'X' : 'O';
//            printf("%c", ch);
//            if (Sacred.isXTurn)
//                SetColor(11, 0);
//            else
//                SetColor(4, 0);
//            gotoXY(_X, _Y);
//            blinkState = !blinkState;
//        }
//
//        // --- Xử lý phím ---
//        if (_kbhit()) {
//            char key = _getch();
//            int col = (_X - Mother_Point_x) / 4;
//            int row = (_Y - Mother_Point_y) / 2;
//
//            if (key == 13 && Sacred.board[row][col] == 0) { // Enter
//                // Đặt quân
//                char ch;
//                if (Sacred.isXTurn) {
//                    SetColor(4, 0);
//                    ch = 'X';
//                    Sacred.board[row][col] = 1;
//                    Sacred.isXTurn = false;
//                }
//                else {
//                    SetColor(11, 0);
//                    ch = 'O';
//                    Sacred.board[row][col] = 2;
//                    Sacred.isXTurn = true;
//                }
//                printf("%c", ch);
//                //SetColor(15, 0);
//                if (Sacred.isXTurn)
//                    SetColor(11, 0);
//                else
//                    SetColor(4, 0);
//                // Trả màu quân trước đó
//                if (!firstMove && Parent.x != -1) {
//                    gotoXY(Parent.x, Parent.y);
//                    if (Sacred.isXTurn)
//                        SetColor(11, 0);
//                    else
//                        SetColor(4, 0);
//                    printf("%c", Sacred.board[(Parent.y - Mother_Point_y) / 2]
//                        [(Parent.x - Mother_Point_x) / 4] == 1 ? 'X' : 'O');
//                }
//
//                // Cập nhật Parent & curPoint
//                Parent = curPoint;
//                curPoint = { _X, _Y };
//                firstMove = false;
//            }
//            else if (key == 'w' || key == 'W') moveUp();
//            else if (key == 's' || key == 'S') moveDown();
//            else if (key == 'a' || key == 'A') moveLeft();
//            else if (key == 'd' || key == 'D') moveRight();
//            else if (key == 'q' || key == 'Q') Menu(Sacred);
//            else if (key == 'l' || key == 'L') {
//                saveGame(Sacred);
//                clearscreen();
//                recoverBoard(Sacred);
//            }
//        }
//
//        Sleep(200); // tốc độ nhấp nháy
//    }
//}
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
            if (Sacred.board[row][col] == 1) {
                print_Target_color_order(CurPa.x, CurPa.y, "X", 4);

               // gotoXY(CurPa.x, CurPa.y); cout<<"R";
            }
            else if (Sacred.board[row][col] == 2) {
                print_Target_color_order(CurPa.x, CurPa.y, "O", 11);
            }
            else {
                
            }
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
            gotoXY(Sacred.CurPoint.x, Mother_Point_y - 2); cout << 0;
            gotoXY(Sacred.CurPoint.y - 4, _Y); cout << 0;
        }
        
   
    }
    else if (BEGIN == 1) // bắt đầu chơi
    {

        Parent.x = -1;
        Parent.y = -1;
        BEGIN = 2;
        _X = Mother_Point_x, _Y = Mother_Point_y;
        gotoXY(_X, _Y);
        print_X_Bright(11, 11);
        print_O_Dark(91, 11);
        SetColor(6, 0);
        square_cell(Sacred.CurPoint.x, Sacred.CurPoint.y);
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
         Parent.x = -1;
         Parent.y = -1;
         resetBoard(Sacred);
         //recoverBoard(Sacred);
        // _X = Mother_Point_x, _Y = Mother_Point_y;
       //  gotoXY(_X, _Y);
         SetColor(6, 0);
         square_cell(_X, _Y);
         CurPa.x = Sacred.CurPoint.x;
         CurPa.y = Sacred.CurPoint.y;
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
    

        Parent.x = -1;
        Parent.y = -1;
        _X = Sacred.CurPoint.x;
        _Y = Sacred.CurPoint.y;
        gotoXY(_X, _Y);
        int temp = Sacred.board[(Sacred.CurPoint.y - Mother_Point_y) / 2][(Sacred.CurPoint.x - Mother_Point_x) / 4];
        gotoXY(Sacred.CurPoint.x, Sacred.CurPoint.y);
        if (temp == 1)
            print_Target_color_order(Sacred.CurPoint.x, Sacred.CurPoint.y, "X", 15);
        else if (temp == 2)
            print_Target_color_order(Sacred.CurPoint.x, Sacred.CurPoint.y, "O", 15);
        

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
                BEGIN = 2;
                Menu();

            }
            else if (key == 13 && Sacred.board[row][col] == 0) {
                gotoXY(0, 25);
                cout << (Parent.x - Mother_Point_x) / 4 << " " << (Parent.y - Mother_Point_y) / 2;
               // Sacred.isNewBoard = false; ////////////////////////////
                if (Parent.x == -1 && Parent.y == -1)
                {
                    print_Step(_X, _Y, "X");
                    Sacred.board[row][col] = 1;
                    Parent.x = _X;
                    Parent.y = _Y;
                    Sacred.isXTurn = false;
                }
                else
                {
                    int temp = Sacred.board[(Parent.y - Mother_Point_y) / 2][(Parent.x - Mother_Point_x) / 4];
                    gotoXY(Parent.x, Parent.y);
                    if (temp == 1)
                        print_Target_color_order(Parent.x, Parent.y, "X", 4);
                    else if (temp == 2)
                        print_Target_color_order(Parent.x, Parent.y, "O", 11);
                    if (!Sacred.isXTurn)
                    {
                        /*gotoXY(Parent.x, Parent.y);
                        SetColor(4, 0);
                        printf("X");*/
                        Sacred.board[row][col] = 2;
                        print_Step(_X, _Y, "O");
                        Sacred.isXTurn = true;
                    }
                    else
                    {
                        /*gotoXY(Parent.x, Parent.y);
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
                    Parent.x = _X;
                    Parent.y = _Y;
                }
                Sacred.CurPoint = { _X,_Y };
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
            case 0:  Sacred.isPVP = true; startGame(); break;
            case 1:  Sacred.isPVP = false;  startGame(); break;
            case 2: cout << "Instructions...\n"; break;
            case 3: displayABOUT(); break;
            case 4: LoadGame();
                /*for (string a : savedGames)
                    cout << a << endl;*/
                break;
            case 5: SETTING(); break;
            case 6:
                cout << "Cam on da choi! Tam biet!\n"; break;
            }
             system("pause");
        }
    }
}
void SETTING()
{
    DebugMode = !DebugMode;
}