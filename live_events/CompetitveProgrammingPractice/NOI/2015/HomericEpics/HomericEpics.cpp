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
typedef pair<ll, ll> simps;
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

int n, k;
ll ans = 0;
priority_queue<simps, vector<simps>, greater<simps>> pq;

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        ll cur;
        cin >> cur;
        pq.push({cur, 0});
    }
    
    if (n == 1) {
        cout << pq.top().first << "\n1\n";
        return 0;
    }

    if (k > 2) while (pq.size() % (k - 1) != 1) pq.push({0, -1e9});
        
    while (pq.size() > 1) {
        ll cur = 0, mx = -1e9;
        for (int i = 0; i < k; i++) {
            cur += pq.top().first;
            setmx(mx, pq.top().second);
            pq.pop();
        }
        ans += cur;
        pq.push({cur, mx + 1});
    }

    cout << ans << "\n" << pq.top().second << "\n";

	return 0;
}
