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

int t;

void subcase() {
    int n, prv = 0;
    ll ans = 0;
    priority_queue<int, vector<int>, greater<int>> pq;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        if (cur < prv) {
            pq.push(prv - cur);
            cur = prv;
        }
        prv = cur;
    }

    int cnt = 0;
    while (pq.size()) {
        ll cur = pq.top();
        ans += (cur - cnt) * (pq.size() + 1);
        cnt = cur;
        pq.pop();
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
