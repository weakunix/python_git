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

const int N = 2e5 + 1;

int n, prime[N], cnt[N], ans = 0;

int main() {
    clr(prime, -1);
    for (ll i = 2; i < N; i++) {
        if (prime[i] != -1) continue;
        prime[i] = i;
        for (ll j = i * i; j < N; j += i) prime[j] = i;
    }

    cnt[1] = 1;
    for (int i = 2; i < N; i++) {
        int cur = i, curcnt = 1;
        while (cur % prime[i] == 0) {
            curcnt++;
            cur /= prime[i];
        }
        cnt[i] = cnt[cur] * curcnt;
    }

    cin >> n;
    for (int i = 1; i < n; i++) ans += cnt[i] * cnt[n - i];
    cout << ans << "\n";

	return 0;
}
