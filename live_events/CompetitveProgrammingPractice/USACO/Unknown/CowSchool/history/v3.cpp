#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 5e4;

struct Frac {
    ll num, den;

    Frac(ll numm = 0, ll denn = 1) {
        num = numm;
        den = denn;

        if (den < 0) {
            num = -num;
            den = -den;
        }

        return;
    }
};

bool operator<(Frac a, Frac b) {
    if (a.num < 0 and b.num > 0) return true;
    if (a.num > 0 and b.num < 0) return false;
    if (a.num < 0 and b.num < 0) {
        a.num = -a.num;
        b.num = -b.num;
        swap(a, b);
    }
    return a.num * b.den < a.den * b.num;
}

int n;
Frac arr[N], x(0, 0);
vector<int> ans;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        arr[i] = Frac(a, b);
        x.num += a;
        x.den += b;
    }
    sort(arr, arr + n);

    for (int i = 0; i < n; i++) {
        x.num -= arr[i].num;
        x.den -= arr[i].den;

        ll mn = 1e18, mx = -1e18;

        for (int j = 0; j <= i; j++) mx = max(arr[j].num * x.den - arr[j].den * x.num, mx);
        for (int j = i + 1; j < n; j++) mn = min(arr[j].num * x.den - arr[j].den * x.num, mn);

        if (mx > mn) ans.push_back(i + 1);
    }

    cout << ans.size() << "\n";
    for (int i : ans) cout << i << "\n";

	return 0;
}
