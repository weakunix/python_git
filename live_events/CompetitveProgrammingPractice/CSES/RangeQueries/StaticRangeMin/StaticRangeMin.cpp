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

int n, q;
vector<int> lg;
vector<vector<int>> sparse(1);

int main() {
    cin >> n >> q;
    lg.resize(n + 1);
    sparse[0].resize(n);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    for (int i = 0; i < n; i++) cin >> sparse[0][i];
    for (int i = 1; (1 << i) <= n; i++) {
        sparse.push_back({});
        for (int j = 0; j + (1 << i) <= n; j++) sparse[i].push_back(min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]));
    }
    for (int i = 0; i < q; i++) {
        int a, b, len;
        cin >> a >> b;
        a--;
        len = lg[b - a];
        cout << min(sparse[len][a], sparse[len][b - (1 << len)]) << "\n";
    }
	return 0;
}
