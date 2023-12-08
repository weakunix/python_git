#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

const int N = 1100010, L = 21;

int n, sparse[L][N], lg[N];
vector<int> stck;
vector<simps> ans;
map<int, set<int>> psbl;

int getsparse(int l, int r) {
    int len = lg[r - l + 1];
    return min(sparse[len][l], sparse[len][r - (1 << len) + 1]);
}

int main() {
    lg[1] = 0;
    for (int i = 2; i < N; i++) lg[i] = lg[i / 2] + 1;

    cin >> n;
    for (int i = 0; i < n; i++) cin >> sparse[0][i];

    for (int i = 1; (1 << i) <= n; i++) {
        for (int j = 0; j + (1 << i) <= n; j++) sparse[i][j] = min(sparse[i - 1][j], sparse[i - 1][j + (1 << (i - 1))]);
    }

    for (int i = n - 1; i >= 0; i--) {
        int cur = sparse[0][i] - i;
        
        if (psbl.count(cur)) {
            int r = *psbl[cur].begin();
            if (getsparse(i, r) == sparse[0][i]) {
                if (ans.empty() or ans.back().second > r) ans.push_back({i, r});
            }
        }

        psbl[cur].insert(i);
        while (stck.size() and sparse[0][stck.back()] < sparse[0][i]) {
            psbl[sparse[0][stck.back()] - stck.back()].erase(stck.back());
            stck.pop_back();
        }
        stck.push_back(i);
    }

    cout << ans.size() << "\n";
    reverse(all(ans));
    for (simps s : ans) cout << s.first + 1 << " " << s.second + 1 << "\n";

	return 0;
}
