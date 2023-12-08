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

const int N = 1100010;

int n, arr[N], seg[4 * N];
vector<int> stck;
vector<simps> ans;
map<int, set<int>> psbl;

void setseg(int node, int l, int r, int idx, int val) {
    if (l > idx or r < idx) return;
    if (l == idx and r == idx) {
        seg[node] = val;
        return;
    }
    int mid = l + (r - l) / 2;
    setseg(2 * node, l, mid, idx, val);
    setseg(2 * node + 1, mid + 1, r, idx, val);
    seg[node] = min(seg[2 * node], seg[2 * node + 1]);
    return;
}

int getseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 1e9;
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return min(getseg(2 * node, l, mid, a, b), getseg(2 * node + 1, mid + 1, r, a, b));
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        setseg(1, 0, n - 1, i, arr[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        int cur = arr[i] - i;
        
        if (psbl.count(cur)) {
            int r = *psbl[cur].begin();
            if (getseg(1, 0, n - 1, i, r) == arr[i]) {
                if (ans.empty() or ans.back().second > r) ans.push_back({i, r});
            }
        }

        psbl[cur].insert(i);
        while (stck.size() and arr[stck.back()] < arr[i]) {
            psbl[arr[stck.back()] - stck.back()].erase(stck.back());
            stck.pop_back();
        }
        stck.push_back(i);
    }

    cout << ans.size() << "\n";
    reverse(all(ans));
    for (simps s : ans) cout << s.first + 1 << " " << s.second + 1 << "\n";

	return 0;
}
