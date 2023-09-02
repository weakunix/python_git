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

int n, cnt[X], sieve[X];

int main() {
    memset(sieve, 0, sizeof(sieve));

    cin >> n;
    for (ll i = 2; i < X; i++) {
        if (sieve[i] != 0) continue;
        sieve[i] = i;
        for (ll j = i * i; j < X; j += i) sieve[j] = i;
    }
    cnt[1] = 1;
    for (int i = 2; i < X; i++) {
        if (sieve[i] == i) {
            cnt[i] = 2;
            continue;
        }
        int cur = i;
        while (cur % sieve[i] == 0) cur /= sieve[i];
        cnt[i] = cnt[cur] + cnt[i / sieve[i]];
    }
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cout << cnt[x] << "\n";
    }
	return 0;
}
