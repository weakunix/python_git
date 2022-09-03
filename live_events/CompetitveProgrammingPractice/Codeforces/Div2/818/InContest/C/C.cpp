#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

int T;

bool Subcase() {
    int N;
    cin >> N;
    vector<int> Cur(N), Tar(N);
    for (int i = 0; i < N; i++) cin >> Cur[i];
    for (int i = 0; i < N; i++) cin >> Tar[i];

    for (int i = 0; i < N; i++) {
        if (Cur[i] > Tar[i]) return false;
    }
    
    while (true) {
        bool Changed = false;
        if (Cur[N - 1] <= Cur[0] and Cur[N - 1] != Tar[N - 1]) {
            Cur[N - 1] = min(Cur[0] + 1, Tar[N - 1]);
            Changed = true;
        }

        for (int i = N - 2; i >= 0; i--) {
            if (Cur[i] <= Cur[i + 1] and Cur[i] != Tar[i]) {
                Cur[i] = min(Cur[i + 1] + 1, Tar[i]);
                Changed = true;
            }
        }

        if (not Changed) break;
    }

    for (int i = 0; i < N; i++) {
        if (Cur[i] != Tar[i]) return false;
    }

    return true;
}

int main() {
    cin >> T;

    for (int i = 0; i < T; i++) {
        if (Subcase()) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
