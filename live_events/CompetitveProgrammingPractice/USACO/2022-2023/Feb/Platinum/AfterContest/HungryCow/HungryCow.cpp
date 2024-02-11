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

const int N = 1e5 + 1, S = 1e7, modval = 1e9 + 7;

struct Node {
    static vector<Node*> s_seg;
    static int s_segidx;

    int _l;
    int _r;
    ll _last;
    ll _rem;
    ll _sm;
    Node* _lc;
    Node* _rc;

    Node() : _l(-1), _r(-1), _last(-1), _rem(0), _sm(0), _lc(nullptr), _rc(nullptr) {}

    Node(int l, int r, ll last, ll rem, ll sm, Node* lc, Node* rc) : _l(l), _r(r), _last(last), _rem(rem), _sm(sm), _lc(lc), _rc(rc)  {}

    ~Node() {}

    void recalc() {
        if (_l == _r) return;

        _rem = 0;
        _sm = 0;
        if (_lc) {
            _rem += _lc->_rem;
            _sm += _lc->_sm;
        }
        if (_rc) {
            _rem += _rc->_rem;
            _sm += _rc->_sm;
        }
        _sm %= modval;

        return;
    }
};

vector<Node*> Node::s_seg(S);
int Node::s_segidx = 0;

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
    delete Node::s_seg[Node::s_segidx];
    Node::s_seg[Node::s_segidx] = new Node(l, r, ord[l] - 1, 0, 0, nullptr, nullptr);
    Node* cur = Node::s_seg[Node::s_segidx];
    Node::s_segidx++;

    if (l == r) {
        cur->_rem = ord[l + 1] - ord[l];
        cur->_sm = (getsm(ord[l + 1] - 1) - getsm(ord[l] - 1) + modval) % modval;
        return cur;
    }

    int mid = l + (r - l) / 2;
    cur->_lc = build(l, mid);
    cur->_rc = build(mid + 1, r);
    cur->recalc();
    return cur;
}

pair<Node*, ll> upd(Node* node, ll& ans, int st, ll cnt) {
    if (not cnt or (node->_r < st or not node->_rem)) return {node, 0};

    if (node->_l == node->_r) {
        ll cur = min(node->_rem, cnt);
        ans = (ans + modval - getsm(node->_last)) % modval;
        ans = (ans + getsm(node->_last + cur)) % modval;
        
        delete Node::s_seg[Node::s_segidx];
        Node::s_seg[Node::s_segidx] = new Node(node->_l, node->_r, node->_last + cur, node->_rem - cur, (getsm(ord[node->_l + 1] - 1) - getsm(node->_last + cur) + modval) % modval, nullptr, nullptr);
        Node* nw = Node::s_seg[Node::s_segidx];
        Node::s_segidx++;
        return {nw, cur};
    }

    if (node->_l >= st and node->_rem <= cnt) {
        ans = (ans + node->_sm) % modval;

        delete Node::s_seg[Node::s_segidx];
        Node::s_seg[Node::s_segidx] = new Node(node->_l, node->_r, -1, 0, 0, nullptr, nullptr);
        Node* nw = Node::s_seg[Node::s_segidx];
        Node::s_segidx++;
        return {nw, node->_rem};
    }

    pair<Node*, ll> res1, res2;
    res1 = upd(node->_lc, ans, st, cnt);
    cnt -= res1.second;
    res2 = upd(node->_rc, ans, st, cnt);

    if (not res1.second and not res2.second) return {node, 0};

    delete Node::s_seg[Node::s_segidx];
    Node::s_seg[Node::s_segidx] = new Node(node->_l, node->_r, -1, 0, 0, res1.first, res2.first);
    Node* nw = Node::s_seg[Node::s_segidx];
    Node::s_segidx++;
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

    int initsegidx = Node::s_segidx, mid = l + (r - l) / 2;
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

    Node::s_segidx = initsegidx;

    return;
}

void dbg(Node* node) { //TODO DEBUG
    if (not node) return;
    cout << node->_l << " " << node->_r << " " << node->_rem << "\n";
    dbg(node->_lc);
    dbg(node->_rc);
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

    for (int i = 0; i < Node::s_segidx; i++) delete Node::s_seg[i];

	return 0;
}
