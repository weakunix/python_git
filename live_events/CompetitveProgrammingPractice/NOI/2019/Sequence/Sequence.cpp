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

const int N = 2e5;

int t, n, k, l, a[N], b[N];
bool visa[N], visb[N];

void subcase() {
    clr(visa, false);
    clr(visb, false);

    cin >> n >> k >> l;
    l = k - l;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    
    ll ans = 0;
    priority_queue<simps> pq[5]; //0: pairs, 1: unmatched a, 2: unmatched b, 3: matched a, 4: matched b
    for (int i = 0; i < n; i++) {
        pq[0].push({a[i] + b[i], i});
        pq[1].push({a[i], i});
        pq[2].push({b[i], i});
    }

    for (int i = 0; i < k; i++) {
        int best[5] = {-1, -1, -1, -1, -1};

        while (pq[0].size() and (visa[pq[0].top().second] or visb[pq[0].top().second])) pq[0].pop();
        while (pq[1].size() and visa[pq[1].top().second]) pq[1].pop();
        while (pq[2].size() and visb[pq[2].top().second]) pq[2].pop();

        if (pq[0].size()) best[0] = pq[0].top().first; //case 0: pair
        if (l and (pq[1].size() and pq[2].size())) best[1] = pq[1].top().first + pq[2].top().first; //case 1: non-pair
        if (pq[3].size() and pq[4].size()) best[2] = pq[3].top().first + pq[4].top().first; //case 2: reroute two pair
        if (pq[4].size() and pq[1].size()) best[3] = pq[4].top().first + pq[1].top().first; //case 3: reroute a pair + non-pair
        if (pq[3].size() and pq[2].size()) best[4] = pq[3].top().first + pq[2].top().first; //case 4: reroute b pair + non-pair

        int mx = *max_element(best, best + 5);
        assert(mx != -1);
        ans += mx;

        if (mx == best[0]) {
            int idx = pq[0].top().second;
            visa[idx] = true;
            visb[idx] = true;
        }
        else if (mx == best[1]) {
            int idxa = pq[1].top().second, idxb = pq[2].top().second;
            visa[idxa] = true;
            visb[idxa] = true;
            visa[idxb] = true;
            visb[idxb] = true;
            pq[3].push({a[idxb], idxb});
            pq[4].push({b[idxa], idxa});
            l--;
        }
        else if (mx == best[2]) {
            pq[3].pop();
            pq[4].pop();
            l++;
        }
        else if (mx == best[3]) {
            int idx = pq[1].top().second;
            pq[4].pop();
            visa[idx] = true;
            visb[idx] = true;
            pq[4].push({b[idx], idx});
        }
        else {
            int idx = pq[2].top().second;
            pq[3].pop();
            visa[idx] = true;
            visb[idx] = true;
            pq[3].push({a[idx], idx});
        }
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
