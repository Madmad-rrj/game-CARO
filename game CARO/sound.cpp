#include <windows.h>
#include <mmsystem.h>
#include "Header.h"
#pragma comment(lib, "Winmm.lib")

// Bật nhạc nền (loop vô hạn, async = chạy song song)
void playBackgroundMusic(const wchar_t* filename) {
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

// Tắt nhạc nền
void stopBackgroundMusic() {
    PlaySound(NULL, 0, 0);
}

// Phát hiệu ứng âm thanh (chỉ phát 1 lần)
void playSFX(const wchar_t* filename) {
    PlaySound(filename, NULL, SND_FILENAME | SND_ASYNC);
}
