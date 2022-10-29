#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef pair<int, int> pi;

int T;

void Subcase() {
    int N, K, R, C;
    cin >> N >> K >> R >> C;
    R--;
    C--;
    
    vector<int> DirX = {K, 0, -K, 0}, DirY = {0, K, 0, -K};
    vector<bool> Row(N), Col(N);
    vector<vector<char> > Res(N, vector<char>(N, '.'));
    queue<pi> CellQ;
    Res[R][C] = 'X';
    CellQ.push({C, R});
    Row[R] = true;
    Col[C] = true;
    
    while (not CellQ.empty()) {
        int x = CellQ.front().first, y = CellQ.front().second;

        CellQ.pop();

        for (int i = 0; i < 4; i++) {
            int curx = x + DirX[i], cury = y + DirY[i];
            
            if (curx < 0 or curx >= N) continue;
            if (cury < 0 or cury >= N) continue;
            if (Res[cury][curx] == 'X') continue;

            Res[cury][curx] = 'X';
            CellQ.push({curx, cury});
            Row[cury] = true;
            Col[curx] = true;
        }
    }

    for (int starty = 0; starty < N; starty++) {
        for (int startx = 0; startx < N; startx++) {
            if (Row[starty] or Col[startx]) continue;
            
            Res[starty][startx] = 'X';
            CellQ.push({startx, starty});
            Row[starty] = true;
            Col[startx] = true;

            while (not CellQ.empty()) {
                int x = CellQ.front().first, y = CellQ.front().second;

                CellQ.pop();

                for (int i = 0; i < 4; i++) {
                    int curx = x + DirX[i], cury = y + DirY[i];
                    
                    if (curx < 0 or curx >= N) continue;
                    if (cury < 0 or cury >= N) continue;
                    if (Res[cury][curx] == 'X') continue;

                    Res[cury][curx] = 'X';
                    CellQ.push({curx, cury});
                    Row[cury] = true;
                    Col[curx] = true;
                }
            }
        }
    }

    for (const vector<char>& v : Res) {
        for (char i : v) cout << i;
        cout << "\n";
    }

    return;
}

int main() {
    cin >> T;

    for (int i = 0; i < T; i++) Subcase();

    return 0;
}
