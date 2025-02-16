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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5;

int n;
ll w[N], c[N], use[N], canrem[N], ans = 0;
priority_queue<simps> pq;

void addedge(int idx, ll cnt) {
    use[idx] += cnt;
    ans += cnt * c[idx];
    canrem[idx] += cnt;
    canrem[idx + 1] += cnt;
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) cin >> c[i];

    for (int i = 1; i < n; i++) {
        ans = 0;

        for (int j = 0; j <= i; j++) canrem[j] = -w[j];

        for (int j = 0; j < i; j++) {
            use[j] = 0;
            addedge(j, max(w[j], w[j + 1]));
            pq.push({c[j], j});
        }

        while (pq.size()) {
            int cur = pq.top().second;
            pq.pop();

            ll cnt = min({canrem[cur], canrem[cur + 1], use[cur]});
            addedge(cur, -cnt);

            if (use[cur] == 0) continue;

            assert(canrem[cur] == 0 or canrem[cur + 1] == 0);
            
            if (canrem[cur] > 0) { //cur + 1 is 0
                if (cur + 1 == i or c[cur + 1] >= c[cur]) continue;
                cnt = min(canrem[cur], use[cur]);
                addedge(cur, -cnt);
                addedge(cur + 1, cnt);
            }
            else if (canrem[cur + 1] > 0) { //cur is 0
                if (cur == 0 or c[cur - 1] >= c[cur]) continue;
                cnt = min(canrem[cur + 1], use[cur]);
                addedge(cur, -cnt);
                addedge(cur - 1, cnt);
            }

            if (cur == 0 or cur + 1 == i or c[cur - 1] + c[cur + 1] >= c[cur]) continue;
            addedge(cur, -use[cur]);
            addedge(cur - 1, use[cur]);
            addedge(cur + 1, use[cur]);
        }

        cout << ans << "\n";
    }

	return 0;
}
