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
#include <cmath>
#include <chrono>
#include <random>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<ll, ll> simps;
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5 + 1, C = 1e6;

int n, cnt;
ll w[N], c[N], st = 0, diff;
vector<simps> v;

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) cin >> c[i];

    v.pb({w[0], C});
    cnt = w[0];
    diff = w[0] * C;

    for (int i = 0; i < n - 1; i++) {
        reverse(all(v));
        for (simps& s : v) s.second *= -1;
        st += diff;
        diff *= -1;

        while (v.size() and v.back().second > 0) {
            ll curcnt = v.back().first, curdiff = v.back().second;
            v.bp();
            cnt -= curcnt;
            diff -= curcnt * curdiff;
        }

        if (cnt < w[i + 1]) {
            v.pb({w[i + 1] - cnt, 0});
            cnt = w[i + 1];
        }

        for (simps& s : v) {
            s.second += c[i];
            diff += s.first * c[i];
        }

        while (cnt > w[i + 1]) {
            ll curcnt = v.back().first, curdiff = v.back().second;

            if (curdiff <= 0) {
                st += diff;
                diff = 0;
                cnt = 0;
                v.clear();
                break;
            }
            
            cnt -= curcnt;
            diff -= curcnt * curdiff;
            v.bp();

            if (cnt < w[i + 1]) {
                v.pb({w[i + 1] - cnt, curdiff});
                diff += (w[i + 1] - cnt) * curdiff;
                cnt = w[i + 1];
            }
        }

        cout << st + diff << "\n";
    }

	return 0;
}
