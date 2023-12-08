#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
const int modval = 1e9 + 7, base = uniform_int_distribution<ll>(30, modval - 1)(rng);

ll thash, curhash = 0, rem = 1;
string s, t, ans;

ll gethash(string str) {
    assert(str.size() <= t.size());
    
    ll res = 0;

    for (char c : str) {
        res = res * base % modval;
        res = (res + (c - 'a') + 1) % modval;
    }

    return res;
}

int main() {
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);

    cin >> s >> t;
    thash = gethash(t);

    for (int i = 0; i < t.size(); i++) rem = rem * base % modval;

    for (char c : s) {
        ans += c;
        curhash = curhash * base % modval;
        curhash = (curhash + (c - 'a') + 1) % modval;
        if (ans.size() > t.size()) curhash = (curhash + modval - rem * ((ans[ans.size() - t.size() - 1] - 'a') + 1) % modval) % modval;

        if (curhash == thash) {
            for (int i = 0; i < t.size(); i++) ans.pop_back();
            curhash = gethash(ans.size() <= t.size() ? ans : ans.substr(ans.size() - t.size(), t.size()));
        }
    }

    cout << ans << "\n";
	return 0;
}
