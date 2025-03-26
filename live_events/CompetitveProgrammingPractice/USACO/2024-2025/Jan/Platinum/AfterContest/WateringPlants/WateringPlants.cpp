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

int n, cnt, rev = 1;
ll w[N], c[N], st = 0, diff, lz = 0;
deque<simps> dq;

simps& getback() {
    return (rev == 1 ? dq.back() : dq.front());
}

void pop() {
    if (rev == 1) dq.bp();
    else dq.pop_front();
    return;
}

void push(simps s) {
    if (rev == 1) dq.pb(s);
    else dq.push_front(s);
    return;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n - 1; i++) cin >> c[i];

    dq.pb({w[0], C});
    cnt = w[0];
    diff = w[0] * C;

    for (int i = 0; i < n - 1; i++) {
        //reverse
        st += diff;
        diff *= -1;
        rev *= -1;
        lz *= -1;

        //prefix min
        while (dq.size() and rev * getback().second + lz > 0) {
            ll curcnt = getback().first, curdiff = rev * getback().second + lz;
            pop();
            cnt -= curcnt;
            diff -= curcnt * curdiff;
        }

        //fill to right limit if too small
        if (cnt < w[i + 1]) {
            push({w[i + 1] - cnt, -lz * rev});
            cnt = w[i + 1];
        }

        //add
        lz += c[i];
        diff += cnt * c[i];

        //cut to right limit if too big
        while (cnt > w[i + 1]) {
            ll curcnt = getback().first, curdiff = rev * getback().second + lz;

            if (curdiff <= 0) {
                st += diff;
                diff = 0;
                cnt = 0;
                rev = 1;
                lz = 0;
                dq.clear();
                break;
            }
            
            cnt -= curcnt;
            diff -= curcnt * curdiff;
            pop();

            if (cnt < w[i + 1]) {
                push({w[i + 1] - cnt, (curdiff - lz) * rev});
                diff += (w[i + 1] - cnt) * curdiff;
                cnt = w[i + 1];
            }
        }

        cout << st + diff << "\n";
    }

	return 0;
}
