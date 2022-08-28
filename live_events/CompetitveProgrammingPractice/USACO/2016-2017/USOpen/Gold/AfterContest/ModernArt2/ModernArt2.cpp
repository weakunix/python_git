#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int N, Cur = 0, Ans = 0;
vector<int> Painting, Count, End, CellStack;

int main() {
    freopen("art2.in", "r", stdin);
    freopen("art2.out", "w", stdout);

    cin >> N;
    Count.resize(N + 1);
    End.resize(N + 1);
    for (int i = 0; i < N; i++) {
        int Color;
        cin >> Color;
        Painting.push_back(Color);
        Count[Color]++;
        End[Color] = i;
    }

    for (int i = 0; i < N; i++) {
        int Color = Painting[i];
        if (Color == 0) {
            if (Cur == 0) continue;
            cout << "-1\n";
            return 0;
        }
        if (Count[Color] == 1) {
            Ans = max(Cur + 1, Ans);
            continue;
        }
        if (i == End[Color]) {
            Ans = max(Cur, Ans);
            for (int j = 0; j < Count[Color] - 1; j++) {
                assert(not CellStack.empty());
                if (CellStack.back() != Color) {
                    cout << "-1\n";
                    return 0;
                }
                CellStack.pop_back();
            }
            Cur--;
            continue;
        }
        if (CellStack.size() == 0 or CellStack.back() != Color) Cur++;
        CellStack.push_back(Color);
    }

    cout << Ans << "\n";

    return 0;
}
