#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <deque>
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

const int N = 5e5, M = 5e5;

int n, m, q, a[N], b[M];
simps qx[N], qy[M];

bool solve() {
    int cura = a[0], curb = b[0];
    deque<simps> newa = {{a[0], a[0]}}, newb = {{b[0], b[0]}};

    for (int i = 1; i < n; i++) {
        if (a[i] > newa.back().first) newa.push_back({a[i], newa.back().second});
        else if (a[i] < newa.back().second) newa.back().second = a[i];
    }
    for (int i = 1; i < m; i++) {
        if (b[i] < newb.back().first) newb.push_back({b[i], newb.back().second});
        else if (b[i] > newb.back().second) newb.back().second = b[i];
    }
   
    while (newa.size() or newb.size()) {
        if (newa.size() and newa.front().first < curb) {
            cura = newa.front().second;
            newa.pop_front();
            continue;
        }
        if (newb.size() and newb.front().first > cura) {
            curb = newb.front().second;
            newb.pop_front();
            continue;
        }
        return false;
    }

    return true;
}

int main() {
    //freopen("expand.in", "r", stdin);
    //freopen("expand.out", "w", stdout);

    cin >> n >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    cout << (solve() ? 1 : 0);
    for (int i = 0; i < q; i++) {
        int kx, ky;
        cin >> kx >> ky;
        for (int j = 0; j < kx; j++) {
            cin >> qx[j].first >> qx[j].second;
            qx[j].first--;
            swap(a[qx[j].first], qx[j].second);
        }
        for (int j = 0; j < ky; j++) {
            cin >> qy[j].first >> qy[j].second;
            qy[j].first--;
            swap(b[qy[j].first], qy[j].second);
        }
        cout << (solve() ? 1 : 0);
        for (int j = 0; j < kx; j++) swap(a[qx[j].first], qx[j].second);
        for (int j = 0; j < ky; j++) swap(b[qy[j].first], qy[j].second);
    }
    cout << "\n";
	return 0;
}
