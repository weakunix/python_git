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
#include <iomanip>
#include <cmath>

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

const int M = 5e4;
const int parr[10] = {0, 500, 2000, 5000, 20000, 40000, 60000, 80000, 100000, 1000000000};
const int iarr[4] = {0, 20000, 50000, 1000000000};
const double eps = 1e-7;

int m;
double pays[M][12], ans = 0;

int cmp(double a, double b) {
    if (fabs(a - b) < eps) return 0;
    return (a < b ? -1 : 1);
}

void pay(double val) {
    val -= 800;
    if (cmp(val, 0) != 1) return;

    double mul = 0.05;

    for (int i = 1; i < 10; i++) {
        if (cmp(val, parr[i]) == 1) {
            ans += mul * (parr[i] - parr[i - 1]);
            mul += 0.05;
            continue;
        }
        ans += mul * (val - parr[i - 1]);
        break;
    }

    return;
}

void income(double val) {
    if (cmp(val, 4000) == 1) val *= 0.8;
    else val -= 800;
    if (cmp(val, 0) != 1) return;

    double mul = 0.2;

    for (int i = 1; i < 4; i++) {
        if (cmp(val, iarr[i]) == 1) {
            ans += mul * (iarr[i] - iarr[i - 1]);
            mul += 0.1;
            continue;
        }
        ans += mul * (val - iarr[i - 1]);
        break;
    }

    return;
}

int main() {
    clr(pays, 0);
    cin >> m;
    while (true) {
        int cur;
        double val;
        string t, date;
        cin >> t;
        if (t == "#") break;
        cin >> cur >> date >> val;
        cur--;
        if (t == "PAY") {
            if (date[1] == '0') pays[cur][9] += val;
            else if (date[1] == '1') pays[cur][10] += val;
            else if (date[1] == '2') pays[cur][11] += val;
            else pays[cur][date[0] - '1'] += val;
        }
        else income(val);
    }

    for (int i = 0; i < m; i++) for (int j = 0; j < 12; j++) pay(pays[i][j]);

    cout << fixed << setprecision(2) << ans << "\n";

	return 0;
}
