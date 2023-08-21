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

const int MX = 18;

int n, q;
vector<vector<int>> par;

int main() {
    cin >> n >> q;
    par.resize(MX, vector<int>(n, -1));
    for (int i = 1; i < n; i++) {
        cin >> par[0][i];
        par[0][i]--;
    }
    for (int i = 1; i < MX; i++) {
        for (int j = 0; j < n; j++) {
            if (par[i - 1][j] == -1) continue;
            par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }
    for (int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        x--;
        for (int i = 0; i < MX; i++) {
            if ((1 << i) & k) {
                x = par[i][x];
                if (x == -1) break;
            }
        }
        cout << (x == -1 ? x : x + 1) << "\n";
    }
	return 0;
}
