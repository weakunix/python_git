#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>

//#include <cstdio>

using namespace std;

const int TotalGridNum = pow(3, 9);

bool IsValidGrid(const vector<vector<int> >& Grid, vector<int>& MustLastX, vector<int>& MustLastY) {
    int tr = 0, mr = 0, br = 0, lc = 0, mc = 0, rc = 0, fd = 0, ld = 0, TotalMoos;
    if (Grid[0][0] + Grid[0][1] + Grid[0][2] == 5 and Grid[0][1] != 1) tr++;
    if (Grid[1][0] + Grid[1][1] + Grid[1][2] == 5 and Grid[1][1] != 1) mr++;
    if (Grid[2][0] + Grid[2][1] + Grid[2][2] == 5 and Grid[2][1] != 1) br++;
    if (Grid[0][0] + Grid[1][0] + Grid[2][0] == 5 and Grid[1][0] != 1) lc++;
    if (Grid[0][1] + Grid[1][1] + Grid[2][1] == 5 and Grid[1][1] != 1) mc++;
    if (Grid[0][2] + Grid[1][2] + Grid[2][2] == 5 and Grid[1][2] != 1) rc++;
    if (Grid[0][0] + Grid[1][1] + Grid[2][2] == 5 and Grid[1][1] != 1) fd++;
    if (Grid[0][2] + Grid[1][1] + Grid[2][0] == 5 and Grid[1][1] != 1) ld++;
    TotalMoos = tr + mr + br + lc + mc + rc + fd + ld;
    if (TotalMoos == 0) return false;
    if (TotalMoos == 1) {
        if (tr == 1) {
            MustLastX = {0, 1, 2};
            MustLastY = {0, 0, 0};
        }
        else if (mr == 1) {
            MustLastX = {0, 1, 2};
            MustLastY = {1, 1, 1};
        }
        else if (br == 1) {
            MustLastX = {0, 1, 2};
            MustLastY = {2, 2, 2};
        }
        else if (lc == 1) {
            MustLastX = {0, 0, 0};
            MustLastY = {0, 1, 2};
        }
        else if (mc == 1) {
            MustLastX = {1, 1, 1};
            MustLastY = {0, 1, 2};
        }
        else if (rc == 1) {
            MustLastX = {2, 2, 2};
            MustLastY = {0, 1, 2};
        }
        else if (fd == 1) {
            MustLastX = {0, 1, 2};
            MustLastY = {0, 1, 2};
        }
        else {
            MustLastX = {0, 1, 2};
            MustLastY = {2, 1, 0};
        }
        return true;
    }
    if (TotalMoos == 2) {
        if (tr + lc + fd == 2) {
            MustLastX = {0};
            MustLastY = {0};
            return true;
        }
        if (tr + mc == 2) {
            MustLastX = {1};
            MustLastY = {0};
            return true;
        }
        if (tr + rc + ld == 2) {
            MustLastX = {2};
            MustLastY = {0};
            return true;
        }
        if (mr + lc == 2) {
            MustLastX = {0};
            MustLastY = {1};
            return true;
        }
        if (mr + mc + fd + ld == 2) {
            MustLastX = {1};
            MustLastY = {1};
            return true;
        }
        if (mr + rc == 2) {
            MustLastX = {2};
            MustLastY = {1};
            return true;
        }
        if (br + lc + ld == 2) {
            MustLastX = {0};
            MustLastY = {2};
            return true;
        }
        if (br + mc == 2) {
            MustLastX = {1};
            MustLastY = {2};
            return true;
        }
        if (br + rc + fd == 2) {
            MustLastX = {2};
            MustLastY = {2};
            return true;
        }
        return false;
    }
    if (TotalMoos == 3) {
        if (tr + lc + fd == 3) {
            MustLastX = {0};
            MustLastY = {0};
            return true;
        }
        if (tr + rc + ld == 3) {
            MustLastX = {2};
            MustLastY = {0};
            return true;
        }
        if (mr + mc + fd + ld == 3) {
            MustLastX = {1};
            MustLastY = {1};
            return true;
        }
        if (br + lc + ld == 3) {
            MustLastX = {0};
            MustLastY = {2};
            return true;
        }
        if (br + rc + fd == 3) {
            MustLastX = {2};
            MustLastY = {2};
            return true;
        }
        return false;
    }
    if (TotalMoos == 4) {
        if (mr + mc + fd + ld == 4) {
            MustLastX = {1};
            MustLastY = {1};
            return true;
        }
        return false;
    }
    return false;
}

void FloodFill(vector<vector<string> >& Visited, queue<int>& XVals, queue<int>& YVals, const int x, const int y) {
    if (Visited[y][x].size() == 3) {
        XVals.push(x);
        YVals.push(y);
        return;
    }
    Visited[y][x] = "#";
    if (Visited[y][x - 1] != "#") FloodFill(Visited, XVals, YVals, x - 1, y);
    if (Visited[y - 1][x] != "#") FloodFill(Visited, XVals, YVals, x, y - 1);
    if (Visited[y][x + 1] != "#") FloodFill(Visited, XVals, YVals, x + 1, y);
    if (Visited[y + 1][x] != "#") FloodFill(Visited, XVals, YVals, x, y + 1);
    return;
}

bool IsSol(vector<vector<string> > Visited, const vector<vector<int> >& TarGrid, const int StartX, const int StartY, const int MustLastX, const int MustLastY) {
    int NumSolved = 0, FailedPapers = 0;
    vector<vector<bool> > TicTacToeVisited(3);
    queue<int> XVals, YVals;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            TicTacToeVisited[y].push_back(false);
            if (TarGrid[y][x] == 0) NumSolved++;
        }
    }
    FloodFill(Visited, XVals, YVals, StartX, StartY);
    while (FailedPapers < XVals.size()) {
        int x = XVals.front(), y = YVals.front(), Letter, TicTacToeX, TicTacToeY;
        string Cur = Visited[y][x];
        if (Cur.size() == 3) {
            if (Cur[0] == 'M') Letter = 1;
            else Letter = 2;
            TicTacToeX = Cur[1] - '1';
            TicTacToeY = Cur[2] - '1';
            XVals.pop();
            YVals.pop();
            if (TicTacToeX == MustLastX and TicTacToeY == MustLastY) {
                if (NumSolved == 8 and Letter == TarGrid[TicTacToeY][TicTacToeX]) return true;
                else {
                    XVals.push(x);
                    YVals.push(y);
                    FailedPapers++;
                }
            }
            else {
                if (TicTacToeVisited[TicTacToeY][TicTacToeX]) {
                    Visited[y][x] = "";
                    FailedPapers = 0;
                    FloodFill(Visited, XVals, YVals, x, y);
                }
                else if (TarGrid[TicTacToeY][TicTacToeX] == Letter) {
                    Visited[y][x] = "";
                    TicTacToeVisited[TicTacToeY][TicTacToeX] = true;
                    NumSolved++;
                    FailedPapers = 0;
                    FloodFill(Visited, XVals, YVals, x, y);
                }
                else {
                    XVals.push(x);
                    YVals.push(y);
                    FailedPapers++;
                }
            }
        }
        else {
            XVals.pop();
            YVals.pop();
        }
    }
    return false;
}

int main() {
    //freopen("test.txt", "r", stdin);
    int N, StartX, StartY, Ans = 0;
    vector<vector<string> > Visited;
    cin >> N;
    for (int i = 0; i < N; i++) {
        vector<string> Row(N);
        Visited.push_back(Row);
    }
    for (int y = 0; y < N; y++) {
        int x = -1;
        string Row, Cur = "";
        cin >> Row;
        for (char c : Row) {
            Cur += c;
            if (Cur.size() == 3) {
                x++;
                if (Cur == "###") Visited[y][x] = "#";
                else if (Cur == "BBB") {
                    StartX = x;
                    StartY = y;
                }
                else if (Cur != "...") Visited[y][x] = Cur;
                Cur = "";
            }
        }
    }
    for (int i = 0; i < TotalGridNum; i++) {
        int Cur = i, Count = TotalGridNum;
        vector<int> MustLastX, MustLastY;
        vector<vector<int> > Grid = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                Count /= 3;
                Grid[y][x] = Cur / Count;
                Cur %= Count;
            }
        }
        if (IsValidGrid(Grid, MustLastX, MustLastY)) {
            for (int j = 0; j < MustLastX.size(); j++) {
                if (IsSol(Visited, Grid, StartX, StartY, MustLastX[j], MustLastY[j])) {
                    Ans++;
                    break;
                }
            }
        }
    }
    cout << Ans << "\n";
    return 0;
}
