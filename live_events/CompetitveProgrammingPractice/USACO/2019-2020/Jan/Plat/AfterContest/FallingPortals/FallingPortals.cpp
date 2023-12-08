#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <complex>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef complex<ll> pt;
typedef pair<ll, ll> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define x real()
#define y imag()

const int N = 2e5;

int n, tar[N];
simps ans[N];
pt arr[N];

bool cmp(int a, int b) {
    return arr[a].y == arr[b].y ? arr[a].x < arr[b].x : arr[a].y < arr[b].y;
}

ll cross(pt a, pt b) {
	return (conj(a) * b).y;
}

simps slope(pt a, pt b) {
    simps res = {a.x - b.x, a.y - b.y};
    if (res.first < 0) {
        res.first *= -1;
        res.second *= -1;
    }
    ll g = gcd(res.first, res.second);
    res.first /= g;
    res.second /= g;
    return res;
}

bool cmpslope(simps a, simps b) { //a < b?
    return a.second * b.first < a.first * b.second;
}

void getans() {
    vector<int> ord(n), hull;
    for (int i = 0; i < n; i++) ord[i] = i;
    sort(all(ord), cmp);

    for (int i : ord) {
        while (hull.size() and arr[hull.back()].x > arr[i].x) hull.pop_back();
        while (hull.size() > 1 and cross(arr[hull.back()] - arr[hull[hull.size() - 2]], arr[i] - arr[hull[hull.size() - 2]]) >= 0) hull.pop_back();
        hull.push_back(i);

        if (arr[tar[i]].y < arr[i].y) continue;

        int l = 0, r = hull.size() - 1;
        while (l < r) {
            int mid = l + (r - l + 1) / 2;
            if (arr[hull[mid]].x > arr[tar[i]].x) {
                r = mid - 1;
                continue;
            }
            simps s1 = slope(arr[hull[mid - 1]], arr[tar[i]]), s2 = slope(arr[hull[mid]], arr[tar[i]]);
            if (cmpslope(s1, s2)) r = mid - 1;
            else l = mid;
        }

        assert(l == r);
        if (arr[hull[l]].x > arr[tar[i]].x) continue;

        simps cur = slope(arr[hull[l]], arr[tar[i]]);
        if (cmpslope(cur, ans[i])) ans[i] = cur;
    }

    return;
}

int main() {
    freopen("falling.in", "r", stdin);
    freopen("falling.out", "w", stdout);

    for (int i = 0; i < N; i++) ans[i] = {1, 2e9};

    cin >> n;
    for (int i = 0; i < n; i++) {
        int cury;
        cin >> cury;
        arr[i] = {i + 1, cury};
    }
    for (int i = 0; i < n; i++) {
        cin >> tar[i];
        tar[i]--;
    }
    
    getans();
    for (int i = 0; i < n; i++) arr[i] = {-arr[i].x, -arr[i].y};
    getans();

    for (int i = 0; i < n; i++) {
        if (ans[i].second == 2e9) cout << "-1\n";
        else cout << ans[i].second << "/" << ans[i].first << "\n";
    }
	return 0;
}
