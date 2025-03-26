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

const int N = 2e5 + 1;

int n, q, a[N], b[N];
ll pfx[N], ans[N];
pair<int, ll> expnd[N]; //expnd[i] = (j, k) where index i - 1 expands to j at a cost of k

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

int main() {
    pfx[0] = 0;
    ans[0] = 0;

    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> a[i] >> b[i];
    sortab();

    expnd[n - 1] = {n - 1, a[n - 1] + b[n - 1]};
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] + b[i] < expnd[i + 1].second + a[i]) expnd[i] = {i, a[i] + b[i]};
        else expnd[i] = {expnd[i + 1].first, expnd[i + 1].second + a[i]};
    }
    
    int cur = -1;
    priority_queue<int> canrem;
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 1; i <= n; i++) {
        if (cur == n - 1) {
            ans[i] = ans[i - 1] + pq.top();
            canrem.push(pq.top());
            pq.pop();
            continue;
        }
        
        int nxt = expnd[cur + 1].first;
        ll cost = expnd[cur + 1].second;
        if (pq.empty() or cost < pq.top()) {
            for (int j = cur + 1; j < nxt; j++) pq.push(b[j]);
            cur = nxt;
            ans[i] = ans[i - 1] + cost;
            canrem.push(b[nxt]);

            while (pq.size() and canrem.top() > pq.top()) {
                int newadd = pq.top(), newrem = canrem.top();
                ans[i] += newadd - newrem;
                pq.pop();
                canrem.pop();
                canrem.push(newadd);
                pq.push(newrem);
            }
        }
        else {
            ans[i] = ans[i - 1] + pq.top();
            canrem.push(pq.top());
            pq.pop();
        }
    }

    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        cout << pfx[n - 1] - ans[k] << "\n";
    }
	return 0;
}
