/*
Test inputs
1:
3
6
1 2 3 1 1 1
3
2 2 3
5
0 0 0 0 0


Test outputs

1:
3
2
0
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        int N, Total = 0, Moves = 0, count, mntv = 0;
        vector<int> Possible;
        cin >> N;
        vector<int> SleepLog(N);
        for (int i = 0; i < N; i++) {
            cin >> SleepLog[i];
        }
        for (int i : SleepLog) {
            Total += i;
            mntv = max(i, mntv);
        }
        for (int FinRes = mntv; FinRes <= Total; FinRes++) {
            if (FinRes == 0 or Total % FinRes == 0) {
                count = 0;
                Moves = 0;
                for (int i : SleepLog) {
                    count += i;
                    if (count > FinRes)
                        break;
                    if (count == FinRes)
                        count = 0;
                    else
                        Moves++;
                }
                if (count == 0) {
                    cout << Moves << "\n";
                    break;
                }
            }
        }
    }
    return 0;
}
