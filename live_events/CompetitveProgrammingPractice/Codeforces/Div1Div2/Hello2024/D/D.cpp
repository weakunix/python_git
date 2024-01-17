#include <iostream>
#include <string>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 2e5 + 1, L = 18;

int t, lg[N];

int getsparse(vector<vector<int>>& sparse, int l, int r) {
    int len = lg[r - l + 1];
    return max(sparse[len][l], sparse[len][r - (1 << len) + 1]);
}

void subcase() {
    int n, mx = 0;
    vector<vector<int>> idx, sparse;

    cin >> n;
    idx.resize(n);
    sparse.resize(L, vector<int>(n));

    for (int i = 0; i < n; i++) {
        cin >> sparse[0][i];
        idx[sparse[0][i]].push_back(i);
        setmx(mx, sparse[0][i]);
    }

    if (idx[0].size() != 1) {
        cout << "NO\n";
        return;
    }

    for (int i = 1; (1 << i) <= n; i++) for (int j = 0; j + i <= n; j++) sparse[i][j] = max(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);

    for (int i = 0; i < mx - 1; i++) {
        idx[i].push_back(n - 1);

        int prv = 0;
        for (int j : idx[i]) {
            if (getsparse(sparse, prv, j) == i) continue;
            auto it = lower_bound(all(idx[i + 1]), prv);
            if (it == idx[i + 1].end() or *it > j) {
                cout << "NO\n";
                return;
            }
            prv = j;
        }
    }

    cout << "YES\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    lg[1] = 0;
    for (int i = 2; i < N; i++) lg[i] = lg[i / 2] + 1;

	cin >> t;

	for (int i = 0; i < t; i++) subcase();

	return 0;
}
