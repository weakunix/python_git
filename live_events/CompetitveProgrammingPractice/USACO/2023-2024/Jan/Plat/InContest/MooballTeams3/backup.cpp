#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
#include <utility>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 3001, modval = 1e9 + 7; //TODO SUBTASK 3

int n, getx[N], gety[N];
simps pts[N];
ll pw[N], ans = 0;

struct BIT {
    int bit[N];

    BIT() {
        clr(bit, 0);
        return;
    }

    int get(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
        return res;
    }

    void set(int idx) {
        for (; idx <= n; idx += idx & (-idx)) bit[idx]++;
    }
};

void solve() {
    for (int i = 0; i < n; i++) {
        getx[pts[i].second] = pts[i].first;
        gety[pts[i].first] = pts[i].second;
    }

    for (int x = 1; x <= n; x++) {
        int y = gety[x];
        ans = (ans + pw[x - 1] * (pw[n - x] - 1)) % modval;
    }

    BIT l, res;

    for (int y = 1; y <= n; y++) {
        int x = getx[y];
        l.set(x);

        int cur = l.get(x);
        ans = (ans + modval - pw[cur - 1] * (pw[n - cur] - 1) % modval) % modval;
    }
}

int main() {
    pw[0] = 1;
    for (int i = 1; i < N; i++) pw[i] = 2 * pw[i - 1] % modval;

    cin >> n;
    for (int i = 0; i < n; i++) cin >> pts[i].first >> pts[i].second;
    solve();
    for (int i = 0; i < n; i++) pts[i] = {n - pts[i].second + 1, pts[i].first};
    solve();

    cout << 2 * ans % modval << "\n";

	return 0;
}
