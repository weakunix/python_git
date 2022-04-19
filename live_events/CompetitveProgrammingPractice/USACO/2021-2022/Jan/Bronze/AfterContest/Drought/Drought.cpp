#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define all(v) v.begin(), v.end()

bool Check(vector<long long>& Hunger, int N) {
    if (Hunger[N - 1] > Hunger[N - 2]) return false;
    long long Reduce;
    for (int i = 1; i < N - 1; i++) {
        if (Hunger[i] > Hunger[i - 1]) {
            Reduce = Hunger[i] - Hunger[i - 1];
            if (Hunger[i + 1] < Reduce) return false;
            Hunger[i] = Hunger[i - 1];
            Hunger[i + 1] -= Reduce;
        }
    }
    return true;
}

int main() {
    int T, N;
    long long Total;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> N;
        Total = 0;
        vector<long long> Hunger;
        for (int i = 0; i < N; i++) {
            long long h;
            cin >> h;
            Hunger.push_back(h);
            Total += h;
        }
        if (N == 1) cout << "0\n";
        else {
            if (Check(Hunger, N)) {
                reverse(all(Hunger));
                if (Check(Hunger, N)) {
                    cout << Total - N * Hunger[0] << "\n";
                }
                else cout << "-1\n";
            }
            else cout << "-1\n";
        }
    }
    return 0;
}
