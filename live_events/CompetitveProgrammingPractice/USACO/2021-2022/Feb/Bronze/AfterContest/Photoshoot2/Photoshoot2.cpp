#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, MaxVal = 0, Ans = 0;
    cin >> N;
    vector<int> CurSeq(N), TarLoc(N + 1);
    for (int i = 0; i < N; i++) cin >> CurSeq[i];
    for (int i = 0; i < N; i++) {
        int b;
        cin >> b;
        TarLoc[b] = i;
    }
    for (int i = 0; i < N; i++) CurSeq[i] = TarLoc[CurSeq[i]];
    for (int i : CurSeq) {
        MaxVal = max(i, MaxVal);
        if (i < MaxVal) Ans++;
    }
    cout << Ans << "\n";
    return 0;
}
