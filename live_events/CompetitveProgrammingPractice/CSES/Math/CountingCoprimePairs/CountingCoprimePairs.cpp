#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
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

const int X = 1e6 + 1;

int n, sieve[X], cnt[X];
ll ans = 0;

int main() {
    memset(sieve, 0, sizeof(sieve));

    for (ll i = 2; i < X; i++) {
        if (sieve[i]) continue;
        sieve[i] = i;
        for (ll j = i * i; j < X; j += i) sieve[j] = i;
    }

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        vector<int> pf;
        cin >> x;
        while (x > 1) {
            int cur = sieve[x];
            pf.push_back(cur);
            while (x % cur == 0) x /= cur;
        }
        assert(pf.size() <= 7);
        for (int j = 1; j < (1 << pf.size()); j++) {
            int cur = 1;
            for (int k = 0; k < pf.size(); k++) {
                if (j & (1 << k)) cur *= pf[k];
            }
            if (__builtin_parity(j)) ans += cnt[cur];
            else ans -= cnt[cur];
            cnt[cur]++;
        }
    }
    cout << (ll) n * (n - 1) / 2 - ans << "\n";
	return 0;
}
