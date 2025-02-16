#include <iostream>
#include <cstdio>
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
#include <numeric>
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

int n, k;
ll sm = 0, ans = -1e18;
vector<int> op1 = {0};
vector<vector<int>> op2 = {{}};
priority_queue<int> rem;

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int t, y;
        cin >> t >> y;
        if (t == 1) {
            op1.pb(y);
            op2.pb({});
        }
        else op2.back().pb(y);
    }

    while (k >= 0 and op1.size()) {
        for (int i : op2.back()) {
            if (i >= 0) sm += i;
            else rem.push(i);
        }
        while (rem.size() > k) {
            sm += rem.top();
            rem.pop();
        }
        setmx(ans, op1.back() + sm);

        op1.bp();
        op2.bp();
        k--;
    }

    cout << ans << "\n";

	return 0;
}
