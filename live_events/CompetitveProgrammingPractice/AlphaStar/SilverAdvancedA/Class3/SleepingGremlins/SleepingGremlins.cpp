#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K, B, Best = 1e5;
    cin >> N >> K >> B;
    vector<int> Sleeping(N + 1);
    for (int i = 0; i < B; i++) {
        int Bridge;
        cin >> Bridge;
        Sleeping[Bridge] = 1;
    }
    for (int i = 1; i <= N; i++) Sleeping[i] += Sleeping[i - 1];
    for (int i = 0; i <= N - K; i++) Best = min(Sleeping[i + K] - Sleeping[i], Best);
    cout << Best << "\n";
    return 0;
}
