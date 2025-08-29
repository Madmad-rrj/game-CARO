#include "Header.h"
#include "Save.h"
using namespace std;
extern bool isPVP;
extern GameRound Sacred;
void display_Enter_Name_Room()
{
    Point pointer;
    system("cls");
    //DrawSquirtle(1, 1);
    Enter_Name_Box();
    Point chP;
    chP.x = 37, chP.y = 9;
    gotoXY(chP.x, chP.y);
    string name = "";
    int time = 1;
    while (time < 3)
    {
        for (int i = 0; i < 16; i++)
        {
            SetColor(i, 0);
            escape_button(2, 1);
        }

        gotoXY(chP.x, chP.y);

        if (_kbhit())
        {
            int ch = _getch();  // đọc 1 phím
            if (ch == 27) 
            {     // ESC
                Menu();        // thoát luôn
            }
            else if (ch == 13) 
            {  // ENTER
                // if (name.size() <= 8) break;
                if (Sacred.isPVP)
                {
                    if (time == 1)
                        Sacred.Name1 = name;
                    else
                        Sacred.Name2 = name;
                    name = "";
                    time++;
                    chP.x = 37;
                    chP.y = 16;
                }
                else
                {
                    if (time == 1)
                        Sacred.Name1 = name;
                    time+=4;
                }
            }
            else if (ch == 8) 
            {   // BACKSPACE
                if (!name.empty()) {
                    name.pop_back();
                    cout << "\b \b";
                }
            }

            else {
                if (name.size() < 8) {
                    name.push_back((char)ch);

                    cout << (char)ch;
                    chP.x++;
                    continue;
                }
                else {
                    // nếu dài quá 8 thì không cho nhập thêm
                }


            }
        }
    }
    if (Sacred.Name1 == "") Sacred.Name1 = "P1";
    if (Sacred.Name2 == "") 
    Sacred.Name2 = (Sacred.isPVP) ? "P2" : "BOT";
    if (!Sacred.isPVP) Sacred.Name2 = "BOT";
}
    //    if (_kbhit())
    //    {
    //        gotoXY(37, 9);
    //        while (true) {
    //            int ch = _getch();  // đọc 1 phím
    //            if (ch == 27) {     // ESC
    //                Menu();        // thoát luôn
    //            }
    //            else if (ch == 13) {  // ENTER
    //                if (name.size() <= 8) break;
    //            }
    //            else if (ch == 8) {   // BACKSPACE
    //                if (!name.empty()) {
    //                    name.pop_back();
    //                    cout << "\b \b";
    //                }
    //            }

    //            else {
    //                if (name.size() < 8) {
    //                    name.push_back((char)ch);
    //                    cout << (char)ch;
    //                }
    //                else {
    //                    // nếu dài quá 8 thì không cho nhập thêm
    //                }
    //            }
    //        }
    //        Sacred.Name1 = name;
    //        name = "";
    //        gotoXY(37, 16);
    //        while (true) {
    //            int ch = _getch();  // đọc 1 phím
    //            if (ch == 27) {     // ESC
    //                Menu();        // thoát luôn
    //            }
    //            else if (ch == 13) {  // ENTER
    //                if (name.size() <= 8) break;
    //            }
    //            else if (ch == 8) {   // BACKSPACE
    //                if (!name.empty()) {
    //                    name.pop_back();
    //                    cout << "\b \b";
    //                }
    //            }

    //            else {
    //                if (name.size() < 8) {
    //                    name.push_back((char)ch);
    //                    cout << (char)ch;
    //                }
    //                else {
    //                    // nếu dài quá 8 thì không cho nhập thêm
    //                }
    //            }
    //        }
    //        Sacred.Name2 = name;
    //        break;
    //    }
    //   
    //}
   

