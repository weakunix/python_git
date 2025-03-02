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
#include <cmath>
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

const double eps = 1e-7;

int n, m, ans = 0;
double best = -1;

int cmp(double a, double b) {
    if (fabs(a - b) < eps) return 0;
    return (a < b ? -1 : 1);
}

int main() {
    cin >> n >> m;
    for (int i = 1; ; i++) {
        double amount = (double) n / i - m;
        if (cmp(amount, 0) != 1) break;
        double cur = 0.3 * sqrt(amount) * i;

        if (cmp(cur, best) == 1) {
            best = cur;
            ans = i;
        }
        else if (cmp(cur, best) == 0) ans = 0;
    }

    cout << ans << "\n";

	return 0;
}
