#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

#define all(v) v.begin(), v.end()

bool IsPossiblePow(vector<int> Targets, int K, const int R) {
    while (K > 0) {
        int Min = Targets.back() - 2 * R;
        K--;
        while (Targets.size() > 0) {
            if (Targets.back() >= Min) Targets.pop_back();
            else break;
        }
        if (Targets.size() == 0) return true;
    }
    return false;
}

int main() {
    int N, K, Low = 0, High = 1e9;
    cin >> N >> K;
    vector<int> Targets(N);
    for (int i = 0; i < N; i++) cin >> Targets[i];
    sort(all(Targets));
    while (Low < High) {
        int Mid = Low + (High - Low) / 2;
        if (IsPossiblePow(Targets, K, Mid)) High = Mid;
        else Low = Mid + 1;
    }
    assert(Low == High);
    cout << Low << "\n";
    return 0;
}
