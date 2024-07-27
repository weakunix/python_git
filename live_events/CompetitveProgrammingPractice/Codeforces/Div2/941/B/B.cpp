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
    int n, k;
    ll cur = 0, sm = 0;
    vector<int> ans;
    cin >> n >> k;
    
    while (sm + (1 << cur) < k) {
        ans.pb(1 << cur);
        sm += 1 << cur;
        cur++;
    }
    ans.pb(k - 1 - sm);

    cur++;
    ans.pb(k + 1);
    ans.pb(1 << cur);
    ans.pb((1 << cur) +  (1 << (cur - 1)));
    while ((1 << cur) <= n) {
        ans.pb(1 << cur);
        cur++;
    }

    cout << ans.size() << "\n";
    for (int i : ans) cout << i << " ";
    cout << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
