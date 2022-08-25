#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;

#define all(v) v.begin(), v.end()

int main() {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);

    const ll XVal = 2019201913, YVal = 2019201949, ModVal = 2019201997;

    int N, K;
    cin >> N >> K;
    vector<ll> MinDist(N, ModVal);
    vector<bool> Visited(N);
    MinDist[0] = 0;

    for (int i = 0; i < N; i++) {
        int Node = -1;

        for (int j = 0; j < N; j++) {
            if (not Visited[j] and (Node == -1 or MinDist[j] < MinDist[Node])) Node = j;
        }

        Visited[Node] = true;

        for (int j = 0; j < N; j++) {
            if (Visited[j]) continue;

            ll x = min(Node, j) + 1, y = max(Node, j) + 1, NewDist = (XVal * x + YVal * y) % ModVal;
            if (NewDist < MinDist[j]) MinDist[j] = NewDist;
        }
    }

    sort(all(MinDist));

    cout << MinDist[N + 1 - K] << "\n";

    return 0;
}
