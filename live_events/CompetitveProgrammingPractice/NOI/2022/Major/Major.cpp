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

struct LLNode {
    int val;
    LLNode* prv;
    LLNode* nxt;

    LLNode() : val(-1), prv(nullptr), nxt(nullptr) {}
    
    LLNode(int ival, LLNode* iprv, LLNode* inxt) : val(ival), prv(iprv), nxt(inxt) {}

    ~LLNode() {}
};

struct SegNode {
    int cnt;
    simps maj;
    SegNode* lc;
    SegNode* rc;

    SegNode() : cnt(0), maj({0, 0}), lc(nullptr), rc(nullptr) {}
    
    ~SegNode() {}
};

const int N = 1e6 + 1;

int n, q;
LLNode* stckf[N];
LLNode* stckb[N];
SegNode* seg[N];

simps addmaj(simps a, simps b) {
    if (a.first == b.first) return {a.first, a.second + b.second};
    else if (a.second > b.second) return {a.first, a.second - b.second};
    return {b.first, b.second - a.second};
}

void updseg(SegNode* node, int l, int r, int val, int c) {
    if (l == r) {
        node->cnt += c;
        node->maj = {val, node->maj.second + c};
        return;
    }
    int mid = l + (r - l) / 2;
    if (val <= mid) {
        if (node->lc == nullptr) node->lc = new SegNode();
        updseg(node->lc, l, mid, val, c);
    }
    else {
        if (node->rc == nullptr) node->rc = new SegNode();
        updseg(node->rc, mid + 1, r, val, c);
    }
    node->cnt = (node->lc == nullptr ? 0 : node->lc->cnt) + (node->rc == nullptr ? 0 : node->rc->cnt);
    node->maj = addmaj(node->lc == nullptr ? make_pair(0ll, 0ll) : node->lc->maj, node->rc == nullptr ? make_pair(0ll, 0ll) : node->rc->maj);
    return;
}

int getseg(SegNode* node, int l, int r, int val) {
    if (l == r) return node->cnt;
    int mid = l + (r - l) / 2;
    if (val <= mid) {
        if (node->lc == nullptr) return 0;
        return getseg(node->lc, l, mid, val);
    }
    if (node->rc == nullptr) return 0;
    return getseg(node->rc, mid + 1, r, val);
}

void mergeseg(SegNode* x, SegNode* y, int l, int r) {
    x->cnt += y->cnt;
    x->maj = addmaj(x->maj, y->maj);
    if (l == r) return;
    int mid = l + (r - l) / 2;

    if (y->lc != nullptr) {
        if (x->lc == nullptr) x->lc = y->lc;
        else mergeseg(x->lc, y->lc, l, mid);
    }

    if (y->rc != nullptr) {
        if (x->rc == nullptr) x->rc = y->rc;
        else mergeseg(x->rc, y->rc, mid + 1, r);
    }

    return;
}

void qadd(int idx, int val) {
    stckb[idx] = new LLNode(val, stckb[idx], nullptr);
    if (stckb[idx]->prv == nullptr) stckf[idx] = stckb[idx];
    else stckb[idx]->prv->nxt = stckb[idx];

    updseg(seg[idx], 1, n + q, val, 1);

    return;
}

void qsub(int idx) {
    int val = stckb[idx]->val;

    if (stckb[idx]->prv == nullptr) {
        delete stckb[idx];
        stckf[idx] = nullptr;
        stckb[idx] = nullptr;
    }
    else {
        stckb[idx] = stckb[idx]->prv;
        delete stckb[idx]->nxt;
        stckb[idx]->nxt = nullptr;
    }

    updseg(seg[idx], 1, n + q, val, -1);

    return;
}

void qmerge(int x, int y, int z) {
    if (stckb[x] != nullptr or stckb[y] != nullptr) {
        if (stckb[x] == nullptr) {
            stckf[z] = stckf[y];
            stckb[z] = stckb[y];
        }
        else if (stckb[y] == nullptr) {
            stckf[z] = stckf[x];
            stckb[z] = stckb[x];
        }
        else {
            stckb[x]->nxt = stckf[y];
            stckf[y]->prv = stckb[x];
            stckf[z] = stckf[x];
            stckb[z] = stckb[y];
        }
    }

    mergeseg(seg[x], seg[y], 1, n + q);
    seg[z] = seg[x];

    return;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    for (int i = 0; i < N; i++) seg[i] = new SegNode();

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        int cur;
        cin >> cur;
        stckb[i] = nullptr;
        for (int j = 0; j < cur; j++) {
            int val;
            cin >> val;
            qadd(i, val);
        }
    }

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            qadd(x, y);
        }
        else if (t == 2) {
            int x;
            cin >> x;
            qsub(x);
        }
        else if (t == 3) {
            int m;
            simps curmaj = {0, 0};
            vector<int> curx;
            cin >> m;
            for (int j = 0; j < m; j++) {
                int x;
                cin >> x;
                
                curx.pb(x);
                curmaj = addmaj(curmaj, seg[x]->maj);
            }

            if (curmaj.first == 0) {
                cout << "-1\n";
                continue;
            }
            
            ll curcnt = 0, totcnt = 0;
            for (int j : curx) {
                curcnt += getseg(seg[j], 1, n + q, curmaj.first);
                totcnt += seg[j]->cnt;
            }
            if (2 * curcnt > totcnt) cout << curmaj.first << "\n";
            else cout << "-1\n";
        }
        else {
            int x, y, z;
            cin >> x >> y >> z;
            qmerge(x, y, z);
        }
    }

	return 0;
}
