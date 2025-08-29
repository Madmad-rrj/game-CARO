#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "Header.h"
#include <windows.h>
using namespace std;

#define TIME_LIMIT 10 // 10 giây

extern std::atomic<bool> isMoveDone; // Đánh dấu đã đi xong#pragma once
void cooldownTimer(int seconds, int posX = 90, int posY = 2);
