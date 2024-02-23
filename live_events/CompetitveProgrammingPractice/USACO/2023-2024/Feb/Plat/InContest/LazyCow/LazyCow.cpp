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

const int N = 2e5, modval = 1e9 + 7;

int n;
simps arr[N];

ll pw(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}

ll getneed(ll a, ll b) {
    return a / b + (a % b != 0);
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;

        int idx = 0;
        ll cnt = 0, ans = 0;
        while (true) {
            ll cur = 0;
            for (int j = 0; j <= i; j++) if (arr[j].first > idx) setmx(cur, getneed(arr[j].second - cnt, arr[j].first - idx));
                
            if (not cur) break;
            idx++;
            cnt += cur;
            ans = (ans + pw(3, cur - 1)) % modval;
        }
        cout << ans << "\n";
    }
	return 0;
}
