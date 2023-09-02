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

int k;
ll n, ans = 0;
vector<ll> primes;

int main() {
    cin >> n >> k;
    primes.resize(k);
    for (int i = 0; i < k; i++) cin >> primes[i];
    for (int i = 1; i < (1 << k); i++) {
        ll cur = 1, cnt = 0;
        bool works = true;
        for (int j = 0; j < k; j++) {
            if (i & (1 << j)) {
                cnt++;
                if (n / cur < primes[j]) {
                    works = false;
                    break;
                }
                cur *= primes[j];
            }
        }
        if (not works) continue;
        if (cnt % 2) ans += n / cur;
        else ans -= n / cur;
    }
    cout << ans << "\n";
	return 0;
}
