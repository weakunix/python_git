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

void explore(int _n, int _m) {
    clr(w, false);

    n = _n;
    m = _m;

    if (n <= 500) solve1();

    return;
}
