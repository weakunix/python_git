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

const int N = 1e5 + 1,  modval = 1e9 + 7;

struct Node {
    int l, r;
    ll last, rem, sm;
    Node *lc, *rc;

    Node(int L = -1, int R = -1, ll LAST = -1, ll REM = 0, Node* LC = nullptr, Node* RC = nullptr) {
        l = L;
        r = R;
        rem = REM;
        last = LAST;
        lc = LC;
        rc = RC;

        return;
    }

    void recalc() {
        if (l == r) return;

        rem = 0;
        sm = 0;
        if (lc) {
            rem += lc->rem;
            sm += lc->sm;
        }
        if (rc) {
            rem += rc->rem;
            sm += rc->sm;
        }
        sm %= modval;

        return;
    }
};

int n, m;
ll ord[N], day[N], bale[N];
set<ll> alld;
map<int, vector<simps>> byday;
map<ll, int> idx;

ll getsm(ll val) {
    val %= modval;
    return val * (val + 1) / 2 % modval;
}

Node* build(int l, int r) {
    Node* cur = new Node(l, r, ord[l] - 1);
    if (l == r) {
        cur->rem = ord[l + 1] - ord[l];
        cur->sm = (getsm(ord[l + 1] - 1) - getsm(ord[l] - 1) + modval) % modval;
        return cur;
    }
    int mid = l + (r - l) / 2;
    cur->lc = build(l, mid);
    cur->rc = build(mid + 1, r);
    cur->recalc();
    return cur;
}

pair<Node*, ll> upd(Node* node, ll& ans, int st, ll cnt) {
    if (not cnt or (node->r < st or not node->rem)) return {node, 0};

    if (node->l == node->r) {
        ll cur = min(node->rem, cnt);
        ans = (ans + modval - getsm(node->last)) % modval;
        ans = (ans + getsm(node->last + cur)) % modval;
        
        Node* nw = new Node(node->l, node->r, node->last + cur, node->rem - cur);
        nw->sm = (getsm(ord[node->l + 1] - 1) - getsm(nw->last) + modval) % modval;
        return {nw, cur};
    }

    if (node->l >= st and node->rem <= cnt) {
        ans = (ans + node->sm) % modval;
        Node* nw = new Node(node->l, node->r, -1, 0);
        return {nw, node->rem};
    }

    pair<Node*, ll> res1, res2;
    res1 = upd(node->lc, ans, st, cnt);
    cnt -= res1.second;
    res2 = upd(node->rc, ans, st, cnt);

    if (not res1.second and not res2.second) return {node, 0};

    Node* nw = new Node(node->l, node->r, -1, 0, res1.first, res2.first);
    nw->recalc();
    return {nw, res1.second + res2.second};
}

void solve(int l, int r, Node* node, ll ans) {
    if (l == r) {
        int d = day[l];
        auto it = lb(all(byday[d]), mkpr((ll) l, (ll) 0));
        if (it != byday[d].begin()) {
            it--;
            if (bale[l] > it->second) upd(node, ans, d, bale[l] - it->second);
        }
        else upd(node, ans, d, bale[l]);
        cout << ans << "\n";
        return;
    }

    int mid = l + (r - l) / 2;
    ll curans = ans;
    vector<int> vals;
    map<int, ll> prv, left, cur;
    Node* curnode = node;

    for (int i = l; i <= r; i++) {
        int d = day[i];
        if (prv.count(d)) setmn(prv[d], bale[i]);
        else {
            vals.pb(d);
            auto it = lb(all(byday[d]), mkpr((ll) l, (ll) 0));
            if (it != byday[d].begin()) {
                it--;
                left[d] = it->second;
            }
            prv[d] = min(bale[i], left[d]);
        }
    }

    //left update

    for (int i = l; i <= mid; i++) {
        int d = day[i];
        if (cur.count(d)) setmn(cur[d], bale[i]);
        else cur[d] = bale[i];
    }

    for (int i : vals) {
        if (not cur.count(i)) cur[i] = 1e18;
        if (prv[i] < min(cur[i], left[i])) curnode = upd(curnode, curans, i, min(cur[i], left[i]) - prv[i]).first;
    }

    solve(l, mid, curnode, curans);

    //right update

    curans = ans;
    cur.clear();
    curnode = node;

    for (int i = l; i <= mid; i++) {
        int d = day[i];
        left[d] = bale[i];
    }

    for (int i = mid + 1; i <= r; i++) {
        int d = day[i];
        if (cur.count(d)) setmn(cur[d], bale[i]);
        else cur[d] = bale[i];
    }
    
    for (int i : vals) {
        if (not cur.count(i)) cur[i] = 1e18;
        if (prv[i] < min(cur[i], left[i])) curnode = upd(curnode, curans, i, min(cur[i], left[i]) - prv[i]).first;
    }

    solve(mid + 1, r, curnode, curans);

    return;
}

void dbg(Node* node) { //TODO DEBUG
    if (not node) return;
    cout << node->l << " " << node->r << " " << node->rem << "\n";
    dbg(node->lc);
    dbg(node->rc);
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> day[i] >> bale[i];
        alld.insert(day[i]);
    }
    m = alld.size();

    for (ll i : alld) {
        ord[idx.size()] = i;
        idx[i] = idx.size();
    }
    ord[m] = 1e18;

    for (int i = 0; i < n; i++) {
        day[i] = idx[day[i]];
        byday[day[i]].push_back({i, bale[i]});
    }

    solve(0, n - 1, build(0, m - 1), 0);

	return 0;
}
