#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

string Subcase() {
    int N, CurIdx;
    string S, Ans = "";
    vector<bool> Moved;
    vector<unordered_set<int> > DigIdx(10);

    cin >> S;

    N = S.size();
    CurIdx = N - 1;
    Moved.resize(N);

    for (int i = 0; i < N; i++) DigIdx[S[i] - '0'].insert(i);

    for (int i = 9; i >= 0; i--) {
        int NoAdd = 0, Add = 0;

        while (not DigIdx[i].empty()) {
            while (CurIdx >= 0 and Moved[CurIdx]) CurIdx--;

            if (DigIdx[i].count(CurIdx) > 0) {
                NoAdd++;
                DigIdx[i].erase(CurIdx);
                CurIdx--;
            }
            else break;
        }

        for (int j : DigIdx[i]) {
            Add++;
            Moved[j] = true;
        }

        for (int j = 0; j < Add; j++) Ans += to_string(min(i + 1, 9));
        for (int j = 0; j < NoAdd; j++) Ans += to_string(i);
    }

    reverse(all(Ans));

    return Ans;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) cout << Subcase() << "\n";

	return 0;
}
