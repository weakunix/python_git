#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_map>
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

const int N = 40;

int n, tar, sz1, sz2;
ll h1[N / 2], h2[N / 2], ans = 0;
unordered_map<ll, ll> cnt1, cnt2;

int main() {
    cnt1.reserve(4096);
    cnt2.reserve(4096);
	cnt1.max_load_factor(0.25);
	cnt2.max_load_factor(0.25);

    cin >> n >> tar;
    sz1 = n / 2;
    sz2 = n - sz1;
    for (int i = 0; i < sz1; i++) cin >> h1[i];
    for (int i = 0; i < sz2; i++) cin >> h2[i];

    for (int i = 0; i < (1 << sz1); i++) {
        ll cursm = 0;
        for (int j = 0; j < sz1; j++) {
            if (i & (1 << j)) cursm += h1[j];
        }
        if (cursm <= tar) cnt1[cursm]++;
    }
    for (int i = 0; i < (1 << sz2); i++) {
        ll cursm = 0;
        for (int j = 0; j < sz2; j++) {
            if (i & (1 << j)) cursm += h2[j];
        }
        if (cursm <= tar) cnt2[cursm]++;
    }

    for (auto u : cnt1) {
        ll cur = tar - u.first;
        if (cnt2.count(cur)) ans += u.second * cnt2[cur];
    }
    cout << ans << "\n";
	return 0;
}
