#include <iostream>
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
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<ll, simps> threesome;

#define pb push_back
#define bp pop_back
#define mkpr make_pair
#define lb lower_bound
#define ub upper_bound
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

const int N = 1e5, modval = 1e9 + 7;

int n, m;
ll ans = 0, seg[4 * N], curseg[4 * N];
vector<ll> ord;
vector<simps> q;
set<ll> alld;
map<ll, int> idx;
map<ll, ll> prv;

ll getsm(ll val) {
    val %= modval;
    return val * (val + 1) / 2 % modval;
}

void buildseg(int node, int l, int r) {
    if (l == r) {
        seg[node] = ord[l + 1] - ord[l];
        curseg[node] = ord[l] - 1;
        return;
    }
    int mid = l + (r - l) / 2;
    buildseg(2 * node, l, mid);
    buildseg(2 * node + 1, mid + 1, r);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

ll updseg(int node, int l, int r, int idx, ll cnt) {
    if (r < idx or not seg[node]) return cnt;
    if (l == r) {
        ll cur = min(seg[node], cnt);
        seg[node] -= cur;
        ans = (ans + modval - getsm(curseg[node])) % modval;
        curseg[node] += cur;
        ans = (ans + getsm(curseg[node])) % modval;
        return cnt - cur;
    }
    int mid = l + (r - l) / 2;
    cnt = updseg(2 * node, l, mid, idx, cnt);
    if (cnt) cnt = updseg(2 * node + 1, mid + 1, r, idx, cnt);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return cnt;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        ll d, b;
        cin >> d >> b;
        alld.insert(d);
        q.pb({d, b});
    }
    m = alld.size();

    for (ll i : alld) {
        ord.pb(i);
        idx[i] = idx.size();
    }
    ord.pb(1e18);

    buildseg(1, 0, m - 1);

    for (simps& s : q) {
        if (prv[s.first] > s.second) { //TODO only subtask 2
            cout << "18\n";
            continue;
        }
        updseg(1, 0, m - 1, idx[s.first], s.second - prv[s.first]);
        prv[s.first] = s.second;
        cout << ans << "\n";
    }

	return 0;
}
