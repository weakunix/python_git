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

const int N = 1e6 + 1, L = 18;

int n, q, par[L][N];

int main() {
    fill(par[0], par[0] + N, 1e6);

    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        par[0][a] = min(b, par[0][a]);
    }

    for (int i = N - 2; i >= 0; i--) par[0][i] = min(par[0][i + 1], par[0][i]);
    for (int i = 1; i < L; i++) for (int j = 0; j < N; j++) par[i][j] = par[i - 1][par[i - 1][j]];

    for (int i = 0; i < q; i++) {
        int a, b, res = 0;
        cin >> a >> b;
        a--; b--;
        for (int i = L - 1; i >= 0; i--) {
            if (par[i][a] <= b) {
                a = par[i][a];
                res |= 1 << i;
            }
        }
        cout << res << "\n";
    }

	return 0;
}
