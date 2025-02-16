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

int cyc[4];
ll a, b, c;

int main() {
    cin >> a >> b >> c;

    a %= 10;
    b %= 4;

    cyc[1] = a;
    cyc[2] = a * a % 10;
    cyc[3] = a * a * a % 10;
    cyc[0] = a * a * a * a % 10;

    ll res = 1;
    while (c) {
        if (c & 1) res = res * b % 4;
        c >>= 1;
        b = b * b % 4;
    }

    cout << cyc[res] << "\n";

	return 0;
}
