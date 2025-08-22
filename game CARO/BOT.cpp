#include "Bot.h"
#include "Header.h"
#include "Save.h"

extern Point Parent;
extern bool DebugMode;
extern int _X, _Y;
int randomInRange(int min, int max) {
    return min + rand() % (max - min + 1);
}
Point randomPoint()
{
    int x, y;
    /*do
    {
        x = randomInRange(3, 6);
        y = randomInRange(3, 6);
    } while (Sacred.board[x][y] != 0);*/
    x = randomInRange(3, 6);
    y = randomInRange(3, 6);
    return { x,y };
}
bool collectInDirectionPVE(const vector<vector<int>>& board,
    int x, int y, int dx, int dy, int limit,
    vector<Point>& PossibleLine)
{
    int n = board.size();
    vector<Point> temp;
    //gotoXY(93, 25); cout << board[x][y]<< " ok "; //Sleep(1000);

    // nếu ô gốc không phải quân mình (2) thì bỏ qua
   // if (board[x][y] != 2) return false;


    gotoXY(93, 25); cout << "Diem dang xet " << x << " " << y << " " << dx << " " << dy;// Sleep(5000);

    int nx = x, ny = y;
    for (int step = 0; step < limit; step++) {
        // ngoài biên => fail
        if (nx < 0 || ny < 0 || nx >= n || ny >= n) return false;

        // gặp quân đối thủ => fail
        if (board[nx][ny] == 1) {
            //cout << "error (" << nx << "," << ny << ")";
            return false;
        }

        temp.push_back({ nx, ny });

        nx += dx;
        ny += dy;
    }
    //gotoXY(0, 25);
    //cout << "temp (" << y << "," << x << ") dx=" << dx << " dy=" << dy
    //    << " size=" << temp.size()
    //    << " valStart=" << board[x][y] << endl; //Sleep(5000);
    if (temp.size() == limit) {
        PossibleLine = temp;
 
        return true;
    }
    return false;
}
bool attack(int needStreak) {
    vector<candidate> candidates;
    if (!Sacred.isXTurn)
        checkBoardPVE(2, Sacred.board, needStreak, candidates);

    for (auto& c : candidates) {
        int dx, dy;
        getDirection(c.status, dx, dy);

        vector<Point> line;
        if (!collectInDirectionPVE(Sacred.board, c.cord.x, c.cord.y, dx, dy, 5, line))
            continue;

        for (Point p : line) {
            if (p.x >= 0 && p.y >= 0 && p.x < BOARD_SIZE && p.y < BOARD_SIZE
                && Sacred.board[p.x][p.y] == 0)
            {
                gotoXY(Mother_Point_x + p.y * 4, Mother_Point_y + p.x * 2);
                cout << "O";
                Sacred.board[p.x][p.y] = 2;
                Sacred.isXTurn = true;
                Parent.x = Mother_Point_x + p.y * 4;
                Parent.y = Mother_Point_y + p.x * 2;
                Sacred.chess_on_board++;
                runGameCheck();
                return true; // đánh thành công
            }
        }
    }
    return false; // không tìm được nước đi
}

bool defend(int needStreak) {
    vector<candidate> candidates;

    // lấy các line của đối thủ (1)
    if (!Sacred.isXTurn)
        checkBoardPVE(1, Sacred.board, needStreak, candidates);

    for (auto& c : candidates) {
        int dx, dy;
        getDirection(c.status, dx, dy);

        vector<Point> line;
        if (!collectInDirectionPVE(Sacred.board, c.cord.x, c.cord.y, dx, dy, 5, line))
            continue;

        for (Point p : line) {
            if (p.x >= 0 && p.y >= 0 && p.x < BOARD_SIZE && p.y < BOARD_SIZE
                && Sacred.board[p.x][p.y] == 0)
            {
                // Vẽ quân O
                gotoXY(Mother_Point_x + p.y * 4, Mother_Point_y + p.x * 2);
                cout << "O";

                // Cập nhật bàn cờ
                Sacred.board[p.x][p.y] = 2;
                Sacred.isXTurn = true;
                Parent.x = Mother_Point_x + p.y * 4;
                Parent.y = Mother_Point_y + p.x * 2;
                Sacred.chess_on_board++;

                runGameCheck();
                return true; // chặn thành công
            }
        }
    }
    return false; // không chặn được
}

//void botMove()
//{
//    // 1. Nếu có thể thắng ngay -> attack 4
//    attack(4);
//
//    // 2. Nếu đối thủ sắp thắng -> defend 4
//    defend(4);
//
//    // 3. Nếu đối thủ có thế mạnh (3 liên tiếp, 2 đầu trống) -> chặn
//    defend(3);
//
//    // 4. Nếu có thể build thế -> attack 3
//    attack(3);
//    attack(2);
//    attack(1);
//
//    // 5. Nếu không có gì đặc biệt thì đánh ngẫu nhiên/chiến lược khác
//   // randomMove();
//}
void getCandidate(
    int streak,
    const vector<vector<int>>& board,
    vector<vector<candidate>>& candidates, // <-- bỏ const
    int mode) // mode 1:X, 2:O
{
    int n = board.size();
    int target = (mode == 1) ? 1 : 2;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] != target) continue;

            for (int dir = 1; dir <= 8; dir++) {
                int dx, dy;
                getDirection(dir, dx, dy);
                auto streakCells = collectInDirection(board, i, j, dx, dy);

                if ((int)streakCells.size() + 1 >= streak) {
                    candidate temp;
                    temp.cord.x = i;
                    temp.cord.y = j;
                    temp.status = dir;
                    temp.streak = streak;
                    candidates[streak].push_back(temp); // hợp lệ
                }
            }
        }
    }
}
bool defending(int streak, vector<vector<candidate>>& candidates, int mode) // mode: 1=open, 2=close
{
    if (candidates[streak].empty()) return false;

    for (auto& cand : candidates[streak])
    {
        int dx, dy;
        getDirection(cand.status, dx, dy);

        int x = cand.cord.x;
        int y = cand.cord.y;

        // --- kiểm tra 2 đầu ---
        int x1 = x - dx, y1 = y - dy; // đầu ngược
        int x2 = x + dx * (streak), y2 = y + dy * (streak); // đầu xuôi

        bool head1_free = (x1 >= 0 && y1 >= 0 && x1 < Sacred.board.size() && y1 < Sacred.board.size() && Sacred.board[x1][y1] == 0);
        bool head2_free = (x2 >= 0 && y2 >= 0 && x2 < Sacred.board.size() && y2 < Sacred.board.size() && Sacred.board[x2][y2] == 0);

        if (mode == 1 && !(head1_free && head2_free)) continue;   // open: cả 2 đầu phải trống
        if (mode == 2 && !(head1_free ^ head2_free)) continue;    // close: đúng 1 đầu trống

        // chọn 1 đầu để chặn
        int nx = head1_free ? x1 : x2;
        int ny = head1_free ? y1 : y2;

        // đánh quân O tại (nx, ny)
        gotoXY(Mother_Point_x + ny * 4, Mother_Point_y + nx * 2);
        cout << "O";
        gotoXY(80, 25);
        cout << "                                      ";
        gotoXY(80, 25);
        if(DebugMode)
        cout << "DEBUG defending, (" << cand.cord.y << ", " << cand.cord.x << ") streak " << cand.streak << " mode " << mode;
        Sacred.board[nx][ny] = 2;
        Sacred.isXTurn = true;
        Parent.x = Mother_Point_x + ny * 4;
        Parent.y = Mother_Point_y + nx * 2;
        Sacred.chess_on_board++;
        runGameCheck();

        return true;
    }
    return false;
}
bool canMakeFiveOneWay(const vector<vector<int>>& board, int x, int y, int dx, int dy) {
    int n = board.size();
    int player = board[x][y];
    //if (player == 0) return false; // ô trống thì không tính

    int count = 1; // đã có quân tại (x,y)
    int nx = x + dx;
    int ny = y + dy;

    while (count < 5 && nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] != 3 - player ) {
        count++;
        nx += dx;
        ny += dy;
    }

    return count >= 5; // true nếu đủ 5 quân liên tiếp theo hướng dx,dy
}

bool attacking(int streak, vector<vector<candidate>>& candidates)
{
    if (candidates[streak].empty()) {
        //cout << "ccccccccccccccc";
        return false;
    }
    int n = candidates[streak].size();
   // printCandidates(candidates[streak]);

    for (int i = 0; i < n; i++)
    {
        int dx, dy;
        getDirection(candidates[streak][i].status, dx, dy);

        int nx = candidates[streak][i].cord.x;
        int ny = candidates[streak][i].cord.y;
        if(!canMakeFiveOneWay(Sacred.board, nx, ny, dx, dy)) continue;
        // đi tiếp streak ô theo hướng đó
        int steps = streak;
        while (steps > 0)
        {
            nx += dx;
            ny += dy;
            steps--;
        }
        // sau khi tính được (nx, ny)
        if (nx < 0 || nx >= Sacred.board.size() || ny < 0 || ny >= Sacred.board.size())
            continue; // bỏ qua candidate này

        if (Sacred.board[nx][ny] != 0)
            continue; // ô đã có quân, không đánh được

        // đánh quân O tại (nx, ny)
        gotoXY(Mother_Point_x + ny * 4, Mother_Point_y + nx * 2);
        cout << "O";
        gotoXY(80, 25); 
        cout << "                                      ";
        gotoXY(80, 25);
        if(DebugMode)
        cout << "DEBUG attacking, (" << candidates[streak][i].cord.y << ", " << candidates[streak][i].cord.x << ") streak " << candidates[streak][i].streak;
        Sacred.board[nx][ny] = 2;        // cập nhật bàn cờ
        Sacred.isXTurn = true;           // chuyển lượt
        Parent.x = Mother_Point_x + ny * 4;
        Parent.y = Mother_Point_y + nx * 2;
        Sacred.chess_on_board++;
        gotoXY(87, 25);
        runGameCheck();                  // kiểm tra thắng thua
        return true;                     // đã đánh xong
    }

    return false; // không tìm được nước đánh hợp lệ
}



void startGamePVE_2()
{
    if (Sacred.chess_on_board == 1)
    {
        Point first_chess = randomPoint();
        gotoXY(Mother_Point_x + first_chess.y * 4, Mother_Point_y + first_chess.x * 2);
        cout << "O";
        Sacred.isXTurn = true;
        Sacred.board[first_chess.x][first_chess.y] = 2;
        Parent.x = Mother_Point_x + first_chess.y * 4;
        Parent.y = Mother_Point_y + first_chess.x * 2;
        Sacred.chess_on_board++;
    }
    else
    {
        //if (Sacred.isXTurn) { gotoXY(0, 26); cout << Sacred.isXTurn<< " LOI"; }
        if (!Sacred.isXTurn)
        {

            //cout << "hello" << Sacred.chess_on_board;

            vector<vector<candidate>> candidates_O(5);
            vector<vector<candidate>> candidates_X(5);
            getCandidate(4, Sacred.board, candidates_X, 1);
            getCandidate(3, Sacred.board, candidates_X, 1);
            getCandidate(4, Sacred.board, candidates_O, 2);
            getCandidate(3, Sacred.board, candidates_O, 2);
            getCandidate(2, Sacred.board, candidates_O, 2);
            getCandidate(1, Sacred.board, candidates_O, 2);
            /*for (int streak = 4; streak > 0; streak++)
                getCandidate(streak, Sacred.board, candidates_O, 2);*/
            //cout << "2222222222222222";

            if (attacking(4, candidates_O)) return;
            if (defending(4, candidates_X, 2)) return;
            if (defending(3, candidates_X, 1)) return;
            if (attacking(3, candidates_O)) return;
            if (attacking(2, candidates_O)) return;
            if (attacking(1, candidates_O)) return;
        }
        
    }
    return;
}

// mode = 0 : trả về 1 hoặc 2 thỏa số quân cờ
// mode = 1 : tìm trả về 1 thỏa số quân cờ
// mode = 2 : tìm trả về 2 thỏa số quân cờ

// vector<Point> &twoHeads,

bool checkBoardPVE(int mode, const vector<vector<int>>& board, int streak, vector<candidate>& candidates)
{
    int n = board.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // lọc theo mode
            if (mode == 0 && board[i][j] == 0) continue;
            else if (mode == 1 && board[i][j] != 1) continue;
            else if (mode == 2 && board[i][j] != 2) continue;

            // thử tất cả 8 hướng
            for (int dir = 1; dir <= 8; dir++) {
                int dx, dy;
                getDirection(dir, dx, dy);

                auto streakCells = collectInDirection(board, i, j, dx, dy);

                if ((int)streakCells.size() + 1 >= streak) {
                    candidate c;
                    c.cord.x = i;
                    c.cord.y = j;
                    c.status = dir;       // lưu đúng hướng
                    c.streak = streak;
                    candidates.push_back(c);
                }
            }
        }
    }
    return !candidates.empty();
}

//
//void getMaxofX(const vector<vector<int>>& board)
//{
//    vector<Point> twoHeads;
//    for (int i = 3; i > 0; i--)
//    {
//
//    }
//}
// (1:doc, 2:ngang, 3: chéo chính, 4 chéo phụ);
//vector<Point> getTwoHeads(Point target, int number, int status)
//{
//    vector<Point>twoHeads;
//    int x = target.x, y = target.y;
//
//    if (status == 1)
//    {
//        if (y > 0) {
//            Point temp;
//            temp.x = x;
//            temp.y = y - 1;
//            twoHeads.push_back(temp);
//        }
//        if (y + number - 1 < BOARD_SIZE)
//        {
//
//        }
//    }
//}
void getDirection(int status, int& dx, int& dy) {
    switch (status) {
    case 1: dx = 1;  dy = 0;  break; // xuống
    case 2: dx = -1; dy = 0;  break; // lên
    case 3: dx = 0;  dy = 1;  break; // phải
    case 4: dx = 0;  dy = -1; break; // trái
    case 5: dx = 1;  dy = 1;  break; // chéo xuống phải
    case 6: dx = -1; dy = -1; break; // chéo lên trái
    case 7: dx = 1;  dy = -1; break; // chéo xuống trái
    case 8: dx = -1; dy = 1;  break; // chéo lên phải
    }
}

//
//vector<Point> getTwoHeads(Point target, int number, int status, const vector<vector<int>>& board)
//{
//    vector<Point> twoHeads;
//    int n = board.size();
//
//    // xác định hướng theo status
//    int dx = 0, dy = 0;
//    if (status == 1) { dx = 1; dy = 0; }      // dọc
//    else if (status == 2) { dx = 0; dy = 1; } // ngang
//    else if (status == 3) { dx = 1; dy = 1; } // chéo chính
//    else if (status == 4) { dx = 1; dy = -1; } // chéo phụ
//
//    // Điểm đầu tiên
//    int x1 = target.x - dx;
//    int y1 = target.y - dy;
//    if (x1 >= 0 && x1 < n && y1 >= 0 && y1 < n && board[x1][y1] == 0) {
//        twoHeads.push_back({ x1, y1 });
//    }
//
//    // Điểm thứ hai xa hon điểm 
//    int x2 = target.x + dx * number;
//    int y2 = target.y + dy * number;
//    if (x2 >= 0 && x2 < n && y2 >= 0 && y2 < n && board[x2][y2] == 0) {
//        twoHeads.push_back({ x2, y2 });
//    }
//
//    return twoHeads;
//}
void printCandidates(const vector<candidate>& candidates) {
    
    for (int i = 0; i < candidates.size(); i++) {
        gotoXY(93, 1 + i);
        
        cout << "DEBUG (" << candidates[i].cord.y << ", " << candidates[i].cord.x << ") streak " << candidates[i].streak << " " << candidates[i].status << endl;
    }
}

//
//void startGamePVE()     // (1:doc, 2:ngang, 3: chéo chính, 4 chéo phụ);
//
//{
//
//    if (Sacred.chess_on_board == 1)
//    {
//        Point first_chess = randomPoint();
//        gotoXY(Mother_Point_x + first_chess.y * 4, Mother_Point_y + first_chess.x * 2);
//        cout << "O";
//        Sacred.isXTurn = true;
//        Sacred.board[first_chess.x][first_chess.y] = 2;
//        Parent.x = Mother_Point_x + first_chess.y * 4;
//        Parent.y = Mother_Point_y + first_chess.x * 2;
//        Sacred.chess_on_board++;
//    }
//    else
//    {
//        vector<Point> winningStreak;
//        gotoXY(93, 1);
//        /* for (int i = 5; i > 1; i--)
//         {
//             if (checkBoardPVE(2, Sacred.board, winningStreak, i, target, status) == 2)
//             {
//                 cout << "DEBUG (" << target.x << ", " << target.y << ")";
//                 cout << endl;
//                 gotoXY(93, 2);
//
//                 switch (status)
//                 {
//                 case 1: cout << " Dọc"; break;
//                 case 2: cout << " ngang"; break;
//                 case 3: cout << u8" chéo chính"; break;
//                 case 4: cout << u8" chéo"; break;
//                 }
//                 vector<Point> twoHeads = getTwoHeads(target, i +1 , status, Sacred.board);
//                 if (!twoHeads.empty()) {
//                     gotoXY(93, 3);         cout << "DEBUG (" << twoHeads[0].x << ", " << twoHeads[0].y << ")";
//
//                     gotoXY(Mother_Point_y + twoHeads[0].y * 2,Mother_Point_x + twoHeads[0].x * 4 );
//                     Sleep(2000);
//                     cout << "O";
//                     Sleep(1000);
//                     Sacred.isXTurn = true;
//                     Sacred.board[twoHeads[0].x][twoHeads[0].y] = 2;
//                     runGameCheck();
//                 }
//                 else {
//                     cout << u8"DEBUG: Không có đầu trống nào để đánh!\n";
//                 }
//
//             }
//         }*/
//        bool flag = true;
//        for (int time = 4; time > -1; time--)
//        {// checkBoardPVE(int mode, const vector<vector<int>>& board, vector<Point>& winningStreak, int int_number, int & status, vector<candidate>& candidates)
//            vector<candidate> candidates;
//            if (!Sacred.isXTurn && checkBoardPVE(2, Sacred.board, time, candidates))
//            {
//                printCandidates(candidates);
//                for (int i = 0; i < candidates.size(); i++)
//                {
//                    if (!flag) break;
//                    for (int i = 0; i < 5; i++)
//                    {
//                        gotoXY(93, i); cout << "                           ";
//
//                    }
//
//                    gotoXY(93, 1);
//                    cout << "DEBUG (" << candidates[i].cord.y << ", " << candidates[i].cord.x << ") streak " << time;
//                    gotoXY(93, 2);
//                    switch (candidates[i].status)
//                    {
//                    case 1: cout << u8" Dọc"; break;
//                    case 2: cout << u8" ngang"; break;
//                    case 3: cout << u8" chéo chính"; break;
//                    case 4: cout << u8" chéo"; break;
//                    }
//                    vector<Point> twoHeads = getTwoHeads(candidates[i].cord, time, candidates[i].status, Sacred.board);
//                    if (!twoHeads.empty())
//                    {
//                        gotoXY(93, 3);        
//                        cout << "Head1 (" << twoHeads[0].y << ", " << twoHeads[0].x << ")";
//                        if (twoHeads.size() == 2)
//                        {
//                            gotoXY(93, 4);         cout << "Head2 (" << twoHeads[1].y << ", " << twoHeads[1].x << ")";
//
//                        }
//
//                        print_O_Bright(91, 11);
//                        print_O_Dark(91, 11);
//                        print_O_Bright(91, 11);
//                        gotoXY(Mother_Point_x + twoHeads[0].y * 4, Mother_Point_y + twoHeads[0].x * 2);
//                        cout << "O";
//                        Sacred.isXTurn = true;
//                        Sacred.board[twoHeads[0].x][twoHeads[0].y] = 2;
//                        Parent.x = Mother_Point_x + twoHeads[0].y * 4;
//                        Parent.y = Mother_Point_y + twoHeads[0].x * 2;
//                        flag = false;
//                        gotoXY(1, 1);
//                        printBoard(Sacred.board);
//                        runGameCheck();
//                    }
//                    else 
//                    {
//                        gotoXY(93, 0);
//                        cout << u8"No path";
//                        //continue;
//                    }
//                }
//
//
//
//
//
//
//                /* cout << "DEBUG (" << target.x << ", " << target.y << ") "<<i;
//                 cout << endl;
//                 gotoXY(93, 2);
//
//                 switch (status)
//                 {
//                 case 1: cout << u8" Dọc"; break;
//                 case 2: cout << u8" ngang"; break;
//                 case 3: cout << u8" chéo chính"; break;
//                 case 4: cout << u8" chéo"; break;
//                 }
//                 vector<Point> twoHeads = getTwoHeads(target, i, status, Sacred.board);
//
//
//                 if (!twoHeads.empty()) {
//                     gotoXY(93, 3);         cout << "Head1 (" << twoHeads[0].x << ", " << twoHeads[0].y << ")";
//                     if (twoHeads.size() == 2)
//                     {
//                         gotoXY(93, 4);         cout << "Head2 (" << twoHeads[1].x << ", " << twoHeads[1].y << ")";
//
//                     }
//
//                     print_O_Bright(91, 11);
//                     print_O_Dark(91, 11);
//                     print_O_Bright(91, 11);
//                     gotoXY(Mother_Point_x + twoHeads[0].y * 4, Mother_Point_y + twoHeads[0].x * 2);
//                     cout << "O";
//                     Sacred.isXTurn = true;
//                     Sacred.board[twoHeads[0].x][twoHeads[0].y] = 2;
//                     Parent.x = Mother_Point_x + twoHeads[0].y * 4;
//                     Parent.y = Mother_Point_y + twoHeads[0].x * 2;
//                     flag = false;
//                     gotoXY(1, 1);
//                     printBoard(Sacred.board);
//                     runGameCheck();
//                 }
//                 else {
//                     cout << u8"DEBUG: Không có đầu trống nào để đánh!\n";
//                 }
//
//             }
//             if (!flag) break;*/
//
//            }
//        }
//    }   
//}
//void collectingChess(const vector<int>& board)
//{
//
//}
vector<candidate>black_list;


//status	dx	dy	Hướng
//1	1	0	xuống
//2 - 1	0	lên
//3	0	1	phải
//4	0 - 1	trái
//5	1	1	chéo xuống phải
//6 - 1 - 1	chéo lên trái
//7	1 - 1	chéo xuống trái
//8 - 1	1	chéo lên phải


//void printCandidatesDebug(const vector<candidate>& candidates) {
//    int baseX = 93;   // cột debug
//    int baseY = 0;    // hàng bắt đầu debug
//
//    // Xoá hết vùng debug cũ (dài bằng số candidates hoặc ít nhất 9 dòng)
//   
//
//    // In lại danh sách candidates
//    for (int i = 0; i < (int)candidates.size(); i++) {
//        gotoXY(baseX, baseY + i);
//        
//    }
//}

