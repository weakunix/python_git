#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 1e5, modval = 1e9 + 7;

int h, w, n;
ll ans = 0;
vector<simps> sts;
map<int, ll> trans, dp;
map<int, threesome> block;
map<int, simps> corr;
map<simps, int> idx;

vector<int> add[N], rem[N], vals[N];

ll calc(int curst) {
    if (dp.count(curst)) return dp[curst];
    int nxt = trans[curst];

    if (not nxt) {
        dp[curst] = 1;
        return 1;
    }

    if (block[nxt].first == 0) dp[curst] = 2 * calc(corr[nxt].second);
    else if (block[nxt].sec == w - 1) dp[curst] = 2 * calc(corr[nxt].first);
    else dp[curst] = calc(corr[nxt].first) + calc(corr[nxt].second);
    dp[curst] %= modval;
    return dp[curst];
}

int main() {
    //freopen("fall.in", "r", stdin);
    //freopen("fall.out", "w", stdout);

    cin >> h >> w >> n;
    for (int i = 0; i < w; i++) {
        sts.push_back({h + 1, i});
        idx[sts[i]] = i;
        vals[i].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        int u, l, r, s;
        cin >> u >> l >> r >> s;
        l--; r--;
        block[u] = {l, {r, s}};
        if (l > 0) {
            sts.push_back({u, l - 1});
            vals[l - 1].push_back(idx.size());
            corr[u].first = idx.size();
            idx[sts.back()] = idx.size();
        }
        if (r < w - 1) {
            sts.push_back({u, r + 1});
            vals[r + 1].push_back(idx.size());
            corr[u].second = idx.size();
            idx[sts.back()] = idx.size();
        }

        add[l].push_back(u);
        rem[r].push_back(u);
    }

    set<int> st = {0};
    for (int i = 0; i < w; i++) {
        for (int j : add[i]) st.insert(j);
        for (int j : vals[i]) {
            auto it = st.upper_bound(sts[j].first);
            it--;
            trans[j] = *it;
        }
        for (int j : rem[i]) st.erase(j);
    }

    for (int i = 0; i < w; i++) ans = (ans + calc(i)) % modval;
    cout << ans << "\n";

	return 0;
}
