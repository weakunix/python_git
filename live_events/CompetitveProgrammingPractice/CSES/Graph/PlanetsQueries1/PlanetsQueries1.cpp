#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 2e5;

int n, q, to[30][N];

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> to[0][i];
        to[0][i]--;
    }
    for (int i = 1; i < 30; i++) {
        for (int j = 0; j < n; j++) to[i][j] = to[i - 1][to[i - 1][j]];
    }
    for (int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        x--;
        for (int j = 0; j < 30; j++) {
            if (k & (1 << j)) x = to[j][x];
        }
        cout << x + 1 << "\n";
    }
	return 0;
}
