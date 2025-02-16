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

int n, ans = 0;
vector<int> v;
map<int, int> detailed;

int getsum() {
    int res = 0;
    for (int i = 1; i <= n; i++) res += abs(i - v[i - 1]);
    return res / 2;
}

int getinv() {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < i; j++) res += (v[j - 1] > v[i - 1]);
    }
    return res;
}


int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) v.pb(i);

    do {
        int sm = getsum(), inv = getinv();
        if (sm == inv) {
            for (int i : v) cout << i << " ";
            cout << "| " << sm << " " << inv << "\n";
        }
        ans += (sm == inv);
        detailed[inv - sm]++;
    }
    while (next_permutation(all(v)));

    cout << "\n----\n\n";
    for (auto& u : detailed) if (u.first) cout << u.first << " " << u.second << "\n";
    cout << "\n----\n\n";
    cout << ans << "\n";

	return 0;
}
