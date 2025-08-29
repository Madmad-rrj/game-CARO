#include "time.h"
#include "Header.h"
std::atomic<bool> isMoveDone = false;
void SetCursorPosition(int x, int y) 
{
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hàm chạy đồng hồ đếm ngược
void cooldownTimer(int seconds, int posX, int posY) {
    for (int i = seconds; i >= 0; --i) {
        if (isMoveDone) {
            // Xóa dòng cooldown khi người chơi đã đi
            gotoXY(posX, posY);
            cout << "                    "; // clear line
            return;
        }

        // Lưu vị trí con trỏ hiện tại
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        COORD oldPos = csbi.dwCursorPosition;

        // In đồng hồ tại vị trí cố định
        gotoXY(posX, posY);
        cout << "Cooldown: " << i << "s   ";

        // Trả lại con trỏ về chỗ cũ
        gotoXY(oldPos.X, oldPos.Y);

        this_thread::sleep_for(chrono::seconds(1));
    }

    // Hết giờ mà chưa đi thì có thể xử lý thêm (ví dụ: tự động bỏ lượt)
    gotoXY(posX, posY);
    cout << "HET GIO!";
}

