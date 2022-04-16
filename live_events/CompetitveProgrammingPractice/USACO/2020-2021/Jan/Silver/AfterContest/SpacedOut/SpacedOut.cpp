#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, TotalBeauty = 0, PrevBeauty;
    cin >> N;
    vector<int> Row(N);
    vector<vector<int> > BeautyRate;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) cin >> Row[x];
        BeautyRate.push_back(Row);
    }
    for (vector<int> v : BeautyRate) {
        int a = 0, b = 0;
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) a += v[i];
            else b += v[i];
        }
        TotalBeauty += max(a, b);
    }
    PrevBeauty = TotalBeauty;
    TotalBeauty = 0;
    for (int x = 0; x < N; x++) {
        int a = 0, b = 0;
        for (int i = 0; i < N; i++) {
            if (i % 2 == 0) a += BeautyRate[i][x];
            else b += BeautyRate[i][x];
        }
        TotalBeauty += max(a, b);
    }
    cout << max(TotalBeauty, PrevBeauty) << "\n";
    return 0;
}
