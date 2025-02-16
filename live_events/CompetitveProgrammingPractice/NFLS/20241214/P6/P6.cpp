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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int L = 9;

int a[L], b[L], c[L], notzeroa, notzerob, notzeroc;
ll ans;
bool carry[L];
string s;

bool eq(int a, int b) {
    return ((a == -1 or b == -1) or a == b);
}

void procstr() {
    int pidx, eidx;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '+') pidx = i;
        if (s[i] == '=') eidx = i;
    }

    for (int i = pidx - 1, j = 0; i >= 0; i--, j++) a[j] = (s[i] == '?' ? -1 : s[i] - '0');
    for (int i = eidx - 1, j = 0; i > pidx; i--, j++) b[j] = (s[i] == '?' ? -1 : s[i] - '0');
    for (int i = s.size() - 1, j = 0; i > eidx; i--, j++) c[j] = (s[i] == '?' ? -1 : s[i] - '0');

    notzeroa = pidx - 1;
    notzerob = eidx - pidx - 2;
    notzeroc = s.size() - eidx - 2;

    if (notzeroa == 0) notzeroa = -1;
    if (notzerob == 0) notzerob = -1;
    if (notzeroc == 0) notzeroc = -1;

    //for (int i = 0; i < L; i++) if (b[i] == -1) swap(a[i], b[i]); //simplify casework

    return;
}

void subcase() {
    clr(a, 0);
    clr(b, 0);
    clr(c, 0);
    ans = 0;

    procstr();

    for (int i = 0; i < (1 << (L - 1)); i++) {
        for (int j = 0; j < L; j++) carry[j] = (1 << j) & i;

        ll cur = 1;
        for (int j = 0; j < L; j++) {
            int cnt = 0;
            bool didcarry = (j != 0 and carry[j - 1]);
            for (int x = 0; x < 10; x++) {
                if (not eq(x, a[j])) continue;
                for (int y = 0; y < 10; y++) {
                    if (not eq(y, b[j])) continue;
                    int val = x + y + didcarry;

                    if (not eq(val % 10, c[j])) continue;
                    if (carry[j] xor (val >= 10)) continue;
                    if (j == notzeroa and x == 0) continue;
                    if (j == notzerob and y == 0) continue;
                    if (j == notzeroc and val % 10 == 0) continue;

                    cnt++;
                }
            }
            cur *= cnt;
        }

        ans += cur;
    }

    cout << ans << "\n";

    return;
}

int main() {
    while (cin >> s) subcase();
	return 0;
}
