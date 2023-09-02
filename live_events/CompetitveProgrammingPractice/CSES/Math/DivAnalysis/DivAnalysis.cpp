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
 
const int modval = 1e9 + 7;
 
int n;
bool alleven = true;
vector<ll> x, k;
ll cnt = 1, sm = 1, prod = 1, prodcnt = 1;
 
ll pw(ll a, int b) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % modval;
        b >>= 1;
        a = a * a % modval;
    }
    return res;
}
 
int main() {
    cin >> n;
    x.resize(n);
    k.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> k[i];
        if (k[i] % 2 == 1) alleven = false;
        cnt = cnt * (k[i] + 1) % modval;
        sm = sm * (pw(x[i], k[i] + 1) - 1) % modval * pw(x[i] - 1, modval - 2) % modval;
    }
    if (alleven) {
        for (int i = 0; i < n; i++) {
            prodcnt = prodcnt * (k[i] + 1) % (modval - 1);
            k[i] /= 2;
        }
    }
    else {
        for (int i = 0; i < n; i++) {
            if (k[i] % 2 == 1 and not alleven) {
                prodcnt = prodcnt * (k[i] + 1) / 2 % (modval - 1);
                alleven = true;
            }
            else prodcnt = prodcnt * (k[i] + 1) % (modval - 1);
        }
    }
    for (int i = 0; i < n; i++) prod = prod * pw(x[i], k[i] * prodcnt % (modval - 1)) % modval;
    cout << cnt << " " << sm << " " << prod << "\n";
	return 0;
}
