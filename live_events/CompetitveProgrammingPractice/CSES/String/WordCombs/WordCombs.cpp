//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx2")

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int m1 = 1e9 + 7, m2 = 1e9 + 9, H = 27;

int n, k;
string tar;
vector<int> ans;
unordered_set<ll> words;

ll gethash(string& s) {
    ll res1 = 0, res2 = 0;
    for (char c : s) {
        res1 = (res1 * H % m1 + (c - 'a') + 1) % m1;
        res2 = (res2 * H % m2 + (c - 'a') + 1) % m2;
    }
    return 2e9 * res1 + res2;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    words.reserve(4096);
    words.max_load_factor(0.25);

    cin >> tar >> k;
    n = tar.size();
    ans.resize(n + 1); ans[n] = 1;
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        if (s.size() <= n) words.insert(gethash(s));
    }
    for (int i = n - 1; i >= 0; i--) {
        ll hsh1 = 0, hsh2 = 0;
        for (int j = i; j < n; j++) {
            hsh1 = (hsh1 * H % m1 + (tar[j] - 'a') + 1) % m1;
            hsh2 = (hsh2 * H % m2 + (tar[j] - 'a') + 1) % m2;
            if (words.count(2e9 * hsh1 + hsh2)) ans[i] = (ans[i] + ans[j + 1]) % m1;
        }
    }
    cout << ans[0] << "\n";
	return 0;
}
