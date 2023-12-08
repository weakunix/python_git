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
multiset<Frac> bestpos, bestneg;

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
        for (int j = 0; j < i; j++) {
            ll a = arr[j].num - arr[i].num, b = arr[j].den - arr[i].den;
            Frac cur(a, b);
            if (b < 0) bestneg.erase(bestneg.find(cur));
            else bestpos.erase(bestpos.find(cur));
        }
        for (int j = i + 1; j < n; j++) {
            ll a = arr[i].num - arr[j].num, b = arr[i].den - arr[j].den;
            Frac cur(a, b);
            if (b < 0) bestneg.insert(cur);
            else bestpos.insert(cur);
        }
        x.num -= arr[i].num;
        x.den -= arr[i].den;

        bool works = false;
        if (bestpos.size()) {
            auto it = bestpos.end();
            it--;
            if (x < *it) works = true;
        }
        if (bestneg.size()) {
            if (*bestneg.begin() < x) works = true;
        }
        if (works) ans.push_back(i + 1);
    }

    cout << ans.size() << "\n";
    for (int i : ans) cout << i << "\n";

	return 0;
}
