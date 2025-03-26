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

const int N = 2e5 + 1; //FIXME (small n only)

int n, q, a[N], b[N];
ll pfx[N];

void sortab() {
    vector<int> newa, newb;
    vector<simps> ord;
    for (int i = 0; i < n; i++) ord.pb({a[i] + b[i], i});
    sort(rall(ord));
    for (simps& s : ord) {
        newa.pb(a[s.second]);
        newb.pb(b[s.second]);
    }
    for (int i = 0; i < n; i++) {
        a[i] = newa[i];
        b[i] = newb[i];
        pfx[i] = (i == 0 ? 0 : pfx[i - 1]) + a[i];
    }
    return;
}

void solve(int k) {
    if (k == 0) {
        cout << pfx[n - 1] << "\n";
        return;
    }

    ll sumb = 0, ans;
    priority_queue<int> pq;

    for (int i = 0; i < k; i++) {
        sumb += b[i];
        pq.push(b[i]);
    }
    
    ans = pfx[k - 1] + sumb;

    for (int i = k; i < n; i++) {
        if (b[i] >= pq.top()) continue;
        sumb -= pq.top();
        pq.pop();
        sumb += b[i];
        pq.push(b[i]);
        setmn(ans, pfx[i] + sumb);
    }

    cout << pfx[n - 1] - ans << "\n";

    return;
}

int main() {
    pfx[0] = 0;

    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    sortab();

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        solve(k);
    }
	return 0;
}
