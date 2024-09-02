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
#include <iomanip>

using namespace std;

const int maxn = 301, maxm = 5010;
const double eps = 1e-8;
int n, m, w, T, V, ind;
double a[maxm];

struct line {
    double x, y, len, k, L, R;
} L[maxm];

struct inter {
    double l, r;
} c[maxn];

bool cmp(const inter &a, const inter &b) {
    return a.l < b.l || (a.l == b.l && a.r < b.r);
}

double f(double x) {
    double s = 0;
    int p = 0;
    for (int i = 1; i <= m; i++) {
        if (L[i].L <= x && x <= L[i].R) {
            c[++p].l = (x - L[i].x) * L[i].k + L[i].y;
            c[p].r = c[p].l + L[i].len;
        }
    }
    if (!p) return 0;
    sort(c + 1, c + p + 1, cmp);
    double l = c[1].l, r = c[1].r;
    for (int i = 2; i <= p; i++) {
        if (c[i].l > r) {
            s += r - l;
            l = c[i].l;
            r = c[i].r;
        } else {
            r = max(c[i].r, r);
        }
    }
    s += (r - l);
    return s;
}

double area() {
    double s = 0;
    for (int i = 2; i <= ind; i++) {
        s += (f(a[i]) + f(a[i-1])) * (a[i] - a[i-1]) / 2;
    }
    return s;
}

void check(double x, double y, double len, double v, double t) {
    L[++m].L = x, L[m].R = x + t, L[m].k = v;
    L[m].x = x, L[m].y = y, L[m].len = len;
    double l = y + t * v, r = y + len + t * v;
    if (r > w + eps) {
        L[m].R = x + (w - len - y) / v;
        check(L[m].R, w - len, len, -v, t - (w - len - y) / v);
    } else if (l < -eps) {
        L[m].R = x - y / v;
        check(L[m].R, 0, len, -v, t + y / v);
    } else {
        a[++ind] = x + t;
    }
    a[++ind] = x;
}

bool cross(int i, int j) {
    return L[i].R >= L[j].L && L[i].L <= L[j].R && fabs(L[i].k - L[j].k) > eps;
}

void get_p(int i, int j) {
    double x1 = L[i].x, x2 = L[j].x, y1 = L[i].y, y2 = L[j].y;
    double k1 = L[i].k, k2 = L[j].k, L1 = L[i].L, L2 = L[j].L;
    double R1 = L[i].R, R2 = L[j].R, len1 = L[i].len, len2 = L[j].len;
    double x = (y2 - y1 + x1 * k1 - x2 * k2) / (k1 - k2);
    if (L1 <= x && x <= R1 && L2 <= x && x <= R2) {
        a[++ind] = x;
    }
    x = (y2 + len2 - y1 + x1 * k1 - x2 * k2) / (k1 - k2);
    if (L1 <= x && x <= R1 && L2 <= x && x <= R2) {
        a[++ind] = x;
    }
    x = (y2 - len1 - y1 + x1 * k1 - x2 * k2) / (k1 - k2);
    if (L1 <= x && x <= R1 && L2 <= x && x <= R2) {
        a[++ind] = x;
    }
    x = (y2 + len2 - len1 - y1 + x1 * k1 - x2 * k2) / (k1 - k2);
    if (L1 <= x && x <= R1 && L2 <= x && x <= R2) {
        a[++ind] = x;
    }
}

int main() {
    scanf("%d%d%d%d", &n, &w, &T, &V);
    for (int i = 1; i <= n; i++) {
        double x, l, v;
        scanf("%lf%lf%lf", &x, &l, &v);
        if (x || l != w) {
            check(0, x, l, v, (double)T);
        } else {
            printf("0.00");
            return 0;
        }
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (i != j && cross(i, j)) {
                get_p(i, j);
            }
        }
    }
    sort(a + 1, a + ind + 1);
    printf("%.2lf\n", (T * w - area()) * V);
    return 0;
}

