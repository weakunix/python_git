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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5 + 1, C = 1e6;

int n;
ll w[N], c[N];
vector<ll> v;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) cin >> c[i];

    for (int i = 0; i <= w[0]; i++) v.pb(i * C);

    for (int i = 0; i < n - 1; i++) {
        reverse(all(v));
        for (int j = 1; j < v.size(); j++) setmn(v[j], v[j - 1]);
        while (v.size() <= w[i + 1]) v.pb(v.back());
        for (int j = 0; j < v.size(); j++) v[j] += j * c[i];
        while (v.size() > w[i + 1] + 1) {
            ll cur = v.back();
            v.bp();
            setmn(v.back(), cur);
        }
        cout << v.back() << "\n";
    }

	return 0;
}
