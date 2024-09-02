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
#include <cmath>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<double, simps> threesome;

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

const int N = 1000, C = 8;
const double eps = 1e-7;

int n, x[N][C], ovr[N];
double avg[C], diff[C], y[N][C], pos[N];
threesome ord[N];

int cmp(double a, double b) {
    if (fabs(a - b) < eps) return 0;
    return (a < b ? -1 : 1);
}

bool scmp(threesome a, threesome b) {
    if (cmp(a.first, b.first) != 0) return cmp(a.first, b.first) == 1;
    if (a.sec == b.sec) return a.sec > b.sec;
    return a.third < b.third;
}

int main() {
    clr(ovr, 0);
    clr(avg, 0);
    clr(diff, 0);
    clr(pos, 0);

    cin >> n;
    for (int i = 0; i < n; i++) for (int j = 0; j < C; j++) cin >> x[i][j];

    for (int i = 0; i < C; i++) {
        for (int j = 0; j < n; j++) avg[i] += x[j][i];
        avg[i] /= n;
    }

    for (int i = 0; i < n; i++) for (int j = 0; j < C; j++) ovr[i] += x[i][j];

    for (int i = 0; i < C; i++) for (int j = 0; j < n; j++) diff[i] += fabs(x[j][i] - avg[i]);

    for (int i = 0; i < n; i++) for (int j = 0; j < C; j++) y[i][j] = (cmp(diff[j], 0) == 0 ? 0 : n * (x[i][j] - avg[j]) / diff[j]);

    for (int i = 0; i < n; i++) for (int j = 0; j < C; j++) pos[i] += (j <= 2 ? 1.0 : 0.8) * y[i][j];

    for (int i = 0; i < n; i++) ord[i] = {pos[i], {ovr[i], i + 1}};

    sort(ord, ord + n, scmp);

    for (int i = 0; i < n; i++) cout << ord[i].third << "\n";

	return 0;
}
