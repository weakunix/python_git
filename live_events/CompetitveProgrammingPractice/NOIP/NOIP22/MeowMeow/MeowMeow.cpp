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

const int N = 301, M = 2e6;

int t, n, m, k, arr[M], vis[2 * N], aux;
vector<threesome> ans;
deque<int> stck[N];
unordered_set<int> avail;

void remavail(int idx) {
    if (stck[idx].size() <= 1) avail.erase(idx);
    return;
}

void addavail(int idx) {
    if (stck[idx].size() <= 1) avail.insert(idx);
    return;
}

void op1(int idx, int cur) {
    ans.pb({1, {aux, -1}});
    ans.pb({2, {idx, aux}});

    remavail(idx);
    stck[idx].pop_front();
    vis[cur] = 0;
    addavail(idx);

    return;
}

void op2(int idx, int cur) {
    ans.pb({1, {idx, -1}});
    
    remavail(idx);
    if (stck[idx].size() and stck[idx].back() == cur) {
        stck[idx].bp();
        vis[cur] = 0;
    }
    else {
        stck[idx].pb(cur);
        vis[cur] = idx;
    }
    addavail(idx);

    return;
}

void subcase() {
    clr(vis, 0);
    ans.clear();
    avail.clear();

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) cin >> arr[i];

    for (int i = 1; i < n; i++) avail.insert(i);
    aux = n;

    for (int i = 0; i < m; i++) {
        int cur = arr[i];

        //cur in a stack
        if (vis[cur]) {
            int idx = vis[cur];
            if (stck[idx][0] == cur) op1(idx, cur);
            else op2(idx, cur);
            continue;
        }

        //cur not in a stack with available stack
        if (avail.size()) {
            int idx = *avail.begin();
            op2(idx, cur);
            continue;
        }

        //special case
        int en = i + 1;
        while (true) {
            int nxt = arr[en];
            if (nxt == cur) break;
            if (vis[nxt] and stck[vis[nxt]][0] == nxt) break;
            en++;
        }

        //no bottom
        if (arr[en] == cur) {
            ans.pb({1, {aux, -1}});
            for (int j = i + 1; j < en; j++) {
                int idx = (vis[arr[j]] ? vis[arr[j]] : *avail.begin());
                op2(idx, arr[j]);
            }
            ans.pb({1, {aux, -1}});
            i = en;
            continue;
        }

        //bottom
        int spec = vis[arr[en]], bot = arr[en], tp = stck[spec].back();
        bool oddcase = false;
        for (int j = i + 1; j < en; j++) if (arr[j] == tp) oddcase = not oddcase;

        //odd
        if (oddcase) {
            op2(aux, cur);

            for (int j = i + 1; j < en; j++) {
                if (arr[j] == tp) {
                    op2(spec, tp);
                    remavail(spec);
                }
                else {
                    int idx = (vis[arr[j]] ? vis[arr[j]] : *avail.begin());
                    op2(idx, arr[j]);
                }
            }

            op2(spec, bot);
            remavail(spec);
            aux = spec;
            i = en;
            continue;
        }

        //even
        op2(spec, cur);

        for (int j = i + 1; j < en; j++) {
            if (arr[j] == tp) op2(spec, tp);
            else {
                int idx = (vis[arr[j]] ? vis[arr[j]] : *avail.begin());
                op2(idx, arr[j]);
            }
        }

        op1(spec, bot);
        vis[tp] = spec;
        i = en;
    }

    cout << ans.size() << "\n";
    for (threesome& t : ans) {
        cout << t.first << " " << t.sec;
        if (t.third != -1) cout << " " << t.third;
        cout << "\n";
    }

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
