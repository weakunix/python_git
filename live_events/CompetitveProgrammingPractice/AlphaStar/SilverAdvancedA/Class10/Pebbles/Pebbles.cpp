#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

int main() {
    int N, Min = 1e9;
    unordered_map<int, int> PebbleIndex;
    cin >> N;
    vector<int> Pebbles(N);
    for (int i = 0; i < N; i++) cin >> Pebbles[i];
    sort(all(Pebbles));
    for (int i = 0; i < N; i++) PebbleIndex[Pebbles[i]] = i;
    for (int i : Pebbles) {
        int RightIndexVal;
        auto RightIndex = upper_bound(all(Pebbles), i + N - 1);
        RightIndex--;
        RightIndexVal = PebbleIndex[*RightIndex];
        if (RightIndexVal - PebbleIndex[i] + 1 != N - 1 or *RightIndex == i + N - 1) Min = min(N - (RightIndexVal - PebbleIndex[i] + 1), Min);
        else Min = min(2, Min);
    }
    cout << Min << "\n" << Pebbles.back() - Pebbles.front() - (N - 2) - min(Pebbles[1] - Pebbles[0], Pebbles[N - 1] - Pebbles[N - 2]) << "\n";
    return 0;
}
