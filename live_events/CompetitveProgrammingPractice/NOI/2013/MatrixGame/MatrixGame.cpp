#include <iostream>
#include <cstdio>
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
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
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

const int modval = 1e9 + 7;

ll a, b, c, d;
string n, m;

ll inv(ll num) {
    ll pw = modval - 2, res = 1;
    while (pw) {
        if (pw & 1) res = res * num % modval;
        pw >>= 1;
        num = num * num % modval;
    }
    return res;
}

ll strpw(ll num, string& s) { //num ^ (s - 1)
    ll res = 1;
    for (char c : s) {
        ll cur = res;
        for (int i = 0; i < 9; i++) res = res * cur % modval;
        for (int i = 0; i < c - '0'; i++) res = res * num % modval;
    }
    return res * inv(num) % modval;
}

ll strmod(string& s) {
    ll res = 0;
    for (char c : s) res = (res * 10 % modval + (c - '0')) % modval;
    return res;
}

ll f(ll num, string& s) { //(num^(s - 1) - 1)/(num - 1)
    if (num == 1) return (strmod(s) - 1 + modval) % modval;
    return (strpw(num, s) - 1 + modval) % modval * inv(num - 1) % modval;
}

int main() {
    cin >> n >> m >> a >> b >> c >> d;

    ll A = strpw(a, m) % modval;
    ll B = f(a, m) * b % modval;
    ll C = A * c % modval;
    ll D = (B * c % modval + d) % modval;

    cout << ((strpw(C, n) + f(C, n) * D % modval) % modval * A % modval + B) % modval << "\n";

	return 0;
}
