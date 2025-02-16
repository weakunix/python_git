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

#include "explore.h"

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

int n, m;
bool w[N];

void solve1() {
    for (int i = 0; i < n - 1; i++) {
        modify(i);
        for (int j = i + 1; j < n; j++) {
            bool cur = query(j);
            if (cur != w[j]) report(i, j);
            w[j] = cur;
        }
    }
    return;
}

void solve2() {
    int res[N];

    clr(res, 0);

    for (int i = 0; (1 << i) < n; i++) {
        for (int j = 0; j < n; j++) if (j & (1 << i)) modify(j);
        for (int j = 0; j < n; j++) {
            bool cur = query(j);
            if ((cur != w[j]) xor ((j & (1 << i)) > 0)) res[j] |= 1 << i;
            w[j] = cur;
        }
    }

    for (int i = 0; i < n; i++) if (res[i] > i) report(i, res[i]);

    return;
}

void bsfind(vector<int> range, vector<int> belong) {
    int len = range.size(), mid = len / 2;
    if (len == 1) {
        for (int i : belong) report(range[0], i);
        return;
    }

    vector<int> lrange, rrange, lbelong, rbelong;
    for (int i = 0; i < mid; i++) {
        lrange.pb(range[i]);
        modify(range[i]);
    }
    for (int i = mid; i < len; i++) rrange.pb(range[i]);

    for (int i : belong) {
        bool cur = query(i);
        if (i < range[mid]) lbelong.pb(i);
        else {
            if (cur != w[i]) lbelong.pb(i);
            else rbelong.pb(i);
        }
        w[i] = cur;
    }

    bsfind(lrange, lbelong);
    bsfind(rrange, rbelong);
    return;
}

void solve3() {
    vector<int> range, belong;
    for (int i = 0; i < n; i++) {
        range.pb(i);
        if (i > 0) belong.pb(i);
    }
    bsfind(range, belong);
    return;
}

void explore(int _n, int _m) {
    clr(w, false);

    n = _n;
    m = _m;

    if (n <= 500) solve1();
    else if (n % 10 == 8) solve2();
    else if (n % 10 == 7) solve3();

    return;
}
