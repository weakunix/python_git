#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

int main() {
    int N, Ans = 40000 * 40000;
    vector<int> SortedXVals, SortedYVals, MinX, MinY, MaxX, MaxY;
    cin >> N;
    vector<int> XVals(N), YVals(N);
    for (int i = 0; i < N; i++) {
        cin >> XVals[i] >> YVals[i];
        SortedXVals.push_back(XVals[i]);
        SortedYVals.push_back(YVals[i]);
    }
    sort(all(SortedXVals));
    sort(all(SortedYVals));
    for (int i = 0; i < 4; i++) {
        MinX.push_back(SortedXVals[i]);
        MaxX.push_back(SortedXVals[N - 1 - i]);
        MinY.push_back(SortedYVals[i]);
        MaxY.push_back(SortedYVals[N - 1 - i]);
    }
    for (int a : MinX) {
        for (int b : MaxX) {
            if (b >= a) {
                for (int c : MinY) {
                    for (int d : MaxY) {
                        if (d >= c) {
                            int Count = 0;
                            for (int i = 0; i < N; i++) {
                                int x = XVals[i], y = YVals[i];
                                if (not ((x >= a and x <= b) and (y >= c and y <= d))) Count++;
                                if (Count > 3) break;
                            }
                            if (Count <= 3) Ans = min((b - a) * (d - c), Ans);
                        }
                    }
                }
            }
        }
    }
    cout << Ans << "\n";
    return 0;
}
