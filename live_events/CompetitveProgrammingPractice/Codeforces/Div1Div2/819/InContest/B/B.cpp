#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

void Subcase() {
    int N, M;
    cin >> N >> M;
    if (N > M) {
        cout << "NO\n";
        return;
    }

    if (N % 2 == 1) {
        cout << "YES\n";
        for (int i = 0; i < N - 1; i++) cout << "1 ";
        cout << M - N + 1 << "\n";
        return;
    }
    
    if (M % 2 == 1) {
        cout << "NO\n";
        return;
    }

    cout << "YES\n";
    for (int i = 0; i < N - 2; i++) cout << "1 ";
    cout << (M - N + 2) / 2 << " " << (M - N + 2) / 2 << "\n";

    return;
}

int main() {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) Subcase();

    return 0;
}
