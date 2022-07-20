#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, Ans = 0;
    vector<int> Pfx = {0}, MinVals(7, -1);
    cin >> N;
    for (int i = 0; i < N; i++) {
        int Id;
        cin >> Id;
        Pfx.push_back((Pfx.back() + Id) % 7);
    }
    for (int i = 0; i <= N; i++) {
        int Val = Pfx[i];
        if (MinVals[Val] == -1) MinVals[Val] = i;
        else Ans = max(i - MinVals[Val], Ans);
    }
    cout << Ans << "\n";
    return 0;
}
