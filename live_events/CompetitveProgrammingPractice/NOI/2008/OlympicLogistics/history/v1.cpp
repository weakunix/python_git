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

const int N = 60;

int n, m, nxt[N], curnxt[N];
double k, c[N], ans = 0;
bool vis[N];

double calc() {
    int indeg[N];
    double curc[N];
    queue<int> q;

    clr(indeg, 0);
    clr(curc, 0);

    for (int i = 0; i < n; i++) indeg[curnxt[i]]++;
    for (int i = 0; i < n; i++) if (not indeg[i]) q.push(i);

    while (q.size()) {
        int node = q.front();
        q.pop();
        curc[node] += c[node];

        int nxtnode = curnxt[node];
        indeg[nxtnode]--;
        curc[nxtnode] += k * curc[node];
        if (not indeg[nxtnode]) q.push(nxtnode);
    }

    if (not indeg[0]) return curc[0];
    
    double v = 0, cnt = k;
    for (int i = curnxt[0]; i != 0; i = curnxt[i], cnt *= k) v = k * v + (curc[i] + c[i]);
    v = k * v + (curc[0] + c[0]);
    
    return v / (1 - cnt);
}

void solve(int curm) {
    return;
}

int main() {
    clr(vis, false);

    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> nxt[i];
        nxt[i]--;
    }
    for (int i = 0; i < n; i++) cin >> c[i];

    int incyc = 0;
    while (not vis[incyc]) {
        vis[incyc] = true;
        incyc = nxt[incyc];
    }

    if (incyc == 0) {
        clr(vis, false);
        vis[0] = true;

        int cur = nxt[0];

        while (cur != 0) {
            vis[cur] = true;

            memcpy(curnxt, nxt, sizeof(nxt));
            curnxt[cur] = 0;

            int curm = m - (nxt[cur] != 0);
            if (curm >= 0) solve(curm);

            cur = nxt[cur];
        }
    }
    else {
        assert(false); //FIXME
    }

    cout << ans << "\n";

	return 0;
}
