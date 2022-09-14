#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int N, M, Ans = 0;
vector<vector<int> > PfxByCol;

int main() {
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);

    cin >> N >> M;
    PfxByCol.resize(N + 1, vector<int>(M));
    for (int y = 1; y <= N; y++) {
        for (int x = 0; x < M; x++) {
            char Cell;
            cin >> Cell;
            PfxByCol[y][x] = PfxByCol[y - 1][x] + (Cell == 'X');
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j++) {
            int Left = 0, Right = 0;

            while (Right < M and PfxByCol[j][Right] - PfxByCol[i - 1][Right] > 0) {
                Right++;
                Left++;
            }

            while (Right < M) {
                if (PfxByCol[j][Right] - PfxByCol[i - 1][Right] == 0) Ans = max((j - i + 1) * (Right - Left + 1), Ans);

                Right++;
                if (PfxByCol[i][Right] - PfxByCol[i - 1][Right] == 1 or PfxByCol[j][Right] - PfxByCol[j - 1][Right] == 1) {
                    Left = Right;
                    while (Right < M and PfxByCol[j][Right] - PfxByCol[i - 1][Right] > 0) {
                        Right++;
                        Left++;
                    }
                }
            }
        }
    }

    cout << Ans << "\n";

    return 0;
}
