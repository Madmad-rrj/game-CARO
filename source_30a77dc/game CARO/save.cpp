#pragma once

#include "Header.h"
#include "Save.h"
#include <conio.h>
#include <fstream>
extern int _X;
extern int _Y;
extern int BEGIN;
vector<string>savedGames;

void saveGame()
{
    enter_fileName_box();
    string name;
    do
    {
        gotoXY(51, 16);
        cin >> name;
        if (name.size() > 8) {
            // gotoXY()
            gotoXY(51, 16); cout << "                                          ";
        }
    } while (name.size() > 8);
    saveToBoard(name);
}
void saveToBoard( string fileName)
{
    string tail = Sacred.isPVP ? "_1" : "_2";
    fileName = fileName + tail + ".txt";
    string filepath = "Save/" + fileName;  // Lưu vào thư mục Saves
    ofstream file(filepath);
    if (!file) cout << "KHONG THE MO FILE";
    // 1. Lượt đi
    file << Sacred.isXTurn << "\n";

    // 2. IsPVP?
    file << Sacred.isPVP << "\n";

    // 2. Điểm số
    file << Sacred.P1 << "\n" << Sacred.P2 << "\n";

    // 3. Số vòng
    file << Sacred.curRound << "\n";

    // 4. Tên người chơi
    file << Sacred.Name1 << "\n" << Sacred.Name2 << "\n";

    // 5. Vị trí con trỏ hiện tại
    file << _X << " " << _Y << "\n";

    // 6. Ma trận bàn cờ    
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            file << Sacred.board[i][j] << " ";

        } file << endl;
    }
    file.close();
    cout << "Da tao file: " << fileName << endl;

}
void readBoard(string fileName)
{
    ifstream fin("Save/" + fileName);
    if (!fin) {
        cerr << "Không thể mở file: " << fileName << endl;
        return;
    }

    // Đọc lượt đi
    fin >> Sacred.isXTurn;

    fin >> Sacred.isPVP;

    // Đọc điểm số
    fin >> Sacred.P1 >> Sacred.P2;

    // Đọc round hiện tại
    fin >> Sacred.curRound;

    // Đọc tên
    fin >> Sacred.Name1 >> Sacred.Name2;

    // Đọc vị trí con trỏ
    fin >> Sacred.CurPoint.x >> Sacred.CurPoint.y;

    bool emptyBoard = true; // kiểm tra có phải bàn trống không
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            fin >> Sacred.board[i][j];
            if (Sacred.board[i][j] != 0) {
                emptyBoard = false;
            }
        }
    }

    Sacred.isNewBoard = emptyBoard;

    fin.close();
}

void readSaveFolder(vector<string>& savedGames, vector<bool>& gamesMode)
{
    // Chạy lệnh dir và ghi đầu ra vào file temp.txt
    system("dir Save > temp.txt");

    ifstream file("temp.txt");
    string line;

    // Đọc từng dòng trong file temp.txt
    while (getline(file, line)) {
        // Kiểm tra xem dòng có chứa .txt hay không và lưu vào vector
        if (line.find(".txt") != string::npos) {
            // Cắt tên file từ dòng
            size_t pos = line.find_last_of(" ");
            savedGames.push_back(line.substr(pos + 1)); // Lưu tên file vào vector
        }
    }

    file.close();
    gamesMode.resize(savedGames.size());
    for (int i = 0; i < savedGames.size(); i++)
    {
        string filename = savedGames[i];
        char modeChar = filename[filename.size() - 5]; // lấy ký tự ngay trước ".txt"
        int mode = modeChar - '0';
        // true = PVP (1), false = PVE (2)
        gamesMode[i] = (mode == 1);
    }

    remove("temp.txt");  // Xóa file tạm sau khi sử dụng
}
void displayLoadGame(int choice, bool isDel)
{
    int x = 49, y = 1;
    vector<bool> gamesMode;
    readSaveFolder(savedGames, gamesMode);
    system("cls");
    int numberOfFile = savedGames.size();
    frameListGame(numberOfFile);
    gotoXY(x, y); cout << "---SAVED GAMES LIST---";

    for (int i = 0; i < numberOfFile; i++)
    {
        if (choice == i)
        {
            gotoXY(x + 4, y + 2 + i); cout << ">";
        }
        gotoXY(x + 6, y + 2 + i); cout << savedGames[i].substr(0, savedGames[i].size() - 6);;
        string temp = (gamesMode[i]) ? "PVP" : "PVE";
        gotoXY(x + 15, y + 2 + i); cout << temp;
    }
    SetColor(15, 0);
    delete_button(48, y + numberOfFile + 4);
    load_button(48, y + numberOfFile + 7);
    SetColor(4, 0);
    (isDel)? delete_button(48, y + numberOfFile + 4): load_button(48, y + numberOfFile + 7);
    SetColor(15, 0);
    //char key = _getch();
}
extern bool flag;
void LoadGame_2(bool ifDel)
{
    int choice = 0;
    char key;
    while (true)
    {
        savedGames.clear();
        displayLoadGame(choice, ifDel);
        int numberOfFile = savedGames.size();
        bool ifempty = savedGames.empty();
        key = _getch();
        if (!ifempty && key == 'w' || key == 'W')
            choice = (choice - 1 + numberOfFile) % numberOfFile;
        else if (!ifempty && key == 's' || key == 'S')
            choice = (choice + 1) % numberOfFile;
        else if (key == 13)
        {
            if (ifempty)
            {
                visualFX(3, []() { No_file_found(); });
                Sleep(1000); // cho người chơi thấy thông báo
                system("cls");
                LoadGame_2(ifDel); // không làm gì thêm
            }

            if (ifDel)
            {
                gotoXY(1, 1);
                cout << savedGames[choice];
                deleteSavedFile(savedGames[choice]);
            }
            else
            {
                gotoXY(1, 1);
                cout << savedGames[choice];
                readBoard(savedGames[choice]);
                BEGIN = 4;
                flag = Sacred.isPVP;
                startGame();
            }
        }

        else if (key == 'q')
        {
            savedGames.clear();
            Menu();
        }
        else if (key == 'd')
        {
            ifDel = true;
            LoadGame_2(ifDel);
        }
        else if (key == 'l')
        {
            ifDel = false;
            LoadGame_2(ifDel);
        }
    }
}
void LoadGame()
{
    int x = 49, y = 1;
    int choice = 0;
    char key;
    vector<bool>gamesMode;
    readSaveFolder(savedGames, gamesMode);
    int numberOfFile = savedGames.size();
    SetColor(15, 0);
    SetConsoleOutputCP(CP_UTF8);
    frameListGame(numberOfFile);
    gotoXY(x, y); cout << "---SAVED GAMES LIST---";
    for (int i = 0; i < numberOfFile; i++)
    {
        gotoXY(x + 6, y + 2 + i); cout << savedGames[i].substr(0, savedGames[i].size() - 6);
        string temp = (gamesMode[i]) ? "PVP" : "PVE";
        gotoXY(x + 15, y + 2 + i); cout << temp;
    }
    bool ifDel;
    while (true)
    {
     /*   SetColor(14, 0);
        delete_button(48, y + numberOfFile + 4);
        load_button(48, y + numberOfFile + 7);
        escape_button(2, 1);
        SetColor(4, 0);
        delete_button(48, y + numberOfFile + 4);
        load_button(48, y + numberOfFile + 7);
        escape_button(2, 1);
        SetColor(15, 0);
        delete_button(48, y + numberOfFile + 4);
        load_button(48, y + numberOfFile + 7);
        escape_button(2, 1);*/

        for (int i = 0; i < 16; i++)
        {
            load_button(48, y + numberOfFile + 7);

            SetColor(i, 0);
            delete_button(48, y + numberOfFile + 4);

            escape_button(2, 1);
        }


        // Nếu có phím được nhấn
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'd' || key == 'D')
            {
                ifDel = true;
                savedGames.clear();
                break;
            }
            else if (key == 'l' || key == 'L')
            {
                ifDel = false;
                savedGames.clear();
                break;
            }
            else if (key == 'q' || key == 27)
            {
                savedGames.clear();
                Menu();
            }
            // nếu không phải d, l, q thì không làm gì => vòng lặp tiếp tục
        }
    }
    LoadGame_2(ifDel);

  
}
void deleteSavedFile(const string& fileName) 
{
    string filePath = "Save/" + fileName; // Tạo đường dẫn đầy đủ đến tệp

    if (remove(filePath.c_str()) != 0) 
    {
        perror("Loi khi xoa tep"); // Thông báo lỗi nếu không xóa được
    }
}