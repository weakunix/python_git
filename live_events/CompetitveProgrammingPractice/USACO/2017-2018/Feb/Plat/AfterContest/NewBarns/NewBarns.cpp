#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const int N = 1e5, L = 17;

int n = 0, q, cnt = 0, treeid[N], par[L][N], ht[N];
simps endpt[N];

int getlca(int a, int b) {
    if (ht[a] < ht[b]) swap(a, b);

    int rem = ht[a] - ht[b], cur = 0;
    while (rem) {
        if (rem & 1) a = par[cur][a];
        rem >>= 1;
        cur++;
    }

    if (a == b) return a;

    for (int i = L - 1; i >= 0; i--) {
        if (par[i][a] != par[i][b]) {
            a = par[i][a];
            b = par[i][b];
        }
    }

    return par[0][a];
}

int getdist(int a, int b) {
   return ht[a] + ht[b] - 2 * ht[getlca(a, b)];
}

int main() {
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);

    memset(par, -1, sizeof(par));

    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        char t;
        cin >> t >> x;
        if (x > 0) x--;

        if (t == 'B') {
            if (x == -1) {
                treeid[n] = cnt;
                ht[n] = 0;
                endpt[cnt] = {n, n};
                cnt++;
            }
            else {
                treeid[n] = treeid[x];
                ht[n] = ht[x] + 1;
                par[0][n] = x;
                for (int i = 1; i < L; i++) par[i][n] = par[i - 1][n] == -1 ? -1 : par[i - 1][par[i - 1][n]];

                int a = endpt[treeid[n]].first, b = endpt[treeid[n]].second;
                if (getdist(a, n) > getdist(a, b)) endpt[treeid[n]] = {a, n};
                if (getdist(b, n) > getdist(endpt[treeid[n]].first, endpt[treeid[n]].second)) endpt[treeid[n]] = {b, n};
            }
            n++;
        }
        else cout << max(getdist(x, endpt[treeid[x]].first), getdist(x, endpt[treeid[x]].second)) << "\n";
    }
	return 0;
}
