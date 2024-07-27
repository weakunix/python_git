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

const int N = 3e5;

int n, k;
ll arr[N], anst;
bool ans[N];
map<ll, vector<int>> times;
priority_queue<simps> pq;

int main() {
    clr(ans, false);

    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 0; i < k; i++) pq.push({-arr[i], i});

    for (int i = k; i < n; i++) {
        int node = pq.top().second;
        ll t = pq.top().first;
        pq.pop();
        times[t].pb(node);
        pq.push({t - arr[i], node});
    }

    anst = pq.top().first;
    ans[pq.top().second] = true;
    pq.pop();

    while (pq.size() and pq.top().first == anst) {
        ans[pq.top().second] = true;
        pq.pop();
    }

    for (auto& u : times) {
        bool works = (u.first == anst);
        for (int i : u.second) {
            if (ans[i]) {
                works = true;
                break;
            }
        }
        if (works) for (int i : u.second) ans[i] = true;
    }

    
    cout << -anst << "\n";
    for (int i = 0; i < k; i++) cout << (ans[i] ? 1 : 0);
    cout << "\n";

	return 0;
}
