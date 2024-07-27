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

ll getinv(vector<int>& v) {
    ll ans = 0;
    vector<int> bit(v.size() + 1);
    for (int i : v) {
        for (int j = i; j > 0; j -= j & (-j)) ans += bit[j];
        for (int j = i; j <= v.size(); j += j & (-j)) bit[j]++;
    }
    return ans % 2;
}

void subcase() {
    int n;
    set<int> allnums;
    map<int, int> mp;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        allnums.insert(a[i]);
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        allnums.insert(b[i]);
    }

    if (allnums.size() > n) {
        cout << "NO\n";
        return;
    }

    for (int i : allnums) mp[i] = mp.size() + 1;

    for (int i = 0; i < n; i++) {
        a[i] = mp[a[i]];
        b[i] = mp[b[i]];
    }

    cout << (getinv(a) == getinv(b) ? "YES\n" : "NO\n");

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
