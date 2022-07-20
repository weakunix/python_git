#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define rall(v) v.rbegin(), v.rend()

int main() {
    int N, MinSpeed = 1e9, Ans = 0;
    cin >> N;
    vector<pii> Cows(N);
    for (int i = 0; i < N; i++) cin >> Cows[i].first >> Cows[i].second;
    sort(rall(Cows));
    for (const pii& p : Cows) {
        if (p.second <= MinSpeed) {
            MinSpeed = p.second;
            Ans++;
        }
    }
    cout << Ans << "\n";
    return 0;
}
