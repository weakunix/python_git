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

void setneg() {
    for (int i = 0; i < n; i++) a[i] *= -1;
    for (int i = 0; i < m; i++) b[i] *= -1;
    return;
}

bool works(vector<int>& va, vector<int>& vb) {
    int cura = va[0], curb = vb[0];
    deque<simps> newa = {{va[0], va[0]}}, newb = {{vb[0], vb[0]}};

    for (int i = 1; i < va.size(); i++) {
        if (va[i] > newa.back().first) newa.push_back({va[i], newa.back().second});
        else if (va[i] < newa.back().second) newa.back().second = va[i];
    }
    for (int i = 1; i < vb.size(); i++) {
        if (vb[i] < newb.back().first) newb.push_back({vb[i], newb.back().second});
        else if (vb[i] > newb.back().second) newb.back().second = vb[i];
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

bool solve(bool needneg) {
    if (needneg) setneg();
    int a1 = 0, a2 = 0, b1 = 0, b2 = 0;
    vector<int> va1, va2, vb1, vb2;
    
    for (int i = 0; i < n; i++) {
        if (a[i] < a[a1]) a1 = i;
        if (a[i] == a[a1]) a2 = i;
    }
    for (int i = 0; i < m; i++) {
        if (b[i] > b[b1]) b1 = i;
        if (b[i] == b[b1]) b2 = i;
    }

    for (int i = 0; i <= a1; i++) va1.push_back(a[i]);
    for (int i = n - 1; i >= a2; i--) va2.push_back(a[i]);
    for (int i = 0; i <= b1; i++) vb1.push_back(b[i]);
    for (int i = m - 1; i >= b2; i--) vb2.push_back(b[i]);

    bool good = (works(va1, vb1) and works(va2, vb2));
    for (int i = a1 + 1; i < a2; i++) if (a[i] > b[b1]) good = false;
    for (int i = b1 + 1; i < b2; i++) if (a[a1] > b[i]) good = false;
    
    if (needneg) setneg();

    return good;
}

int main() {
    //freopen("expand.in", "r", stdin);
    //freopen("expand.out", "w", stdout);

    cin >> n >> n >> m >> q;
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    cout << (solve(a[0] > b[0]) ? 1 : 0);
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

        if (a[0] == b[0]) cout << 0;
        else cout << (solve(a[0] > b[0]) ? 1 : 0);
        
        for (int j = 0; j < kx; j++) swap(a[qx[j].first], qx[j].second);
        for (int j = 0; j < ky; j++) swap(b[qy[j].first], qy[j].second);
    }
    cout << "\n";
	return 0;
}
