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

const int N = 1e6;

int n, a[N];
ll ans = 0;
vector<simps> ord;
set<int> seen;

int getlidx(int idx) {
    auto it = seen.lb(idx);
    if (it == seen.begin()) return -1;
    it--;
    return *it;
}

int getridx(int idx) {
    auto it = seen.ub(idx);
    if (it == seen.end()) return n;
    return *it;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ord.pb({a[i], i});
    }

    sort(rall(ord));

    for (simps& s : ord) {
        int idx = s.second, val = s.first, l = getlidx(idx), r = getridx(idx);
        
        //odd range: left point from [l + 1, idx], right point from [idx, r - 1]
        ll lsz = idx - l, rsz = r - idx, tot = ((lsz + 1) / 2) * ((rsz + 1) / 2) + (lsz / 2) * (rsz / 2);
        ans += tot * val;

        //even range (including l): left point from [morel + 1, l], right point from [idx, r - 1]
        if (l != -1) {
            int morel = getlidx(l), morelsz = idx - morel;
            tot = ((morelsz + 1) / 2 - (lsz + 1) / 2) * (rsz / 2) + (morelsz / 2 - lsz / 2) * ((rsz + 1) / 2);
            ans += tot * val;
        }

        //even range (including r): left point from [l + 1, idx], right point from [r, morer - 1]
        if (r != n) {
            int morer = getridx(r), morersz = morer - idx;
            tot = ((lsz + 1) / 2) * (morersz / 2 - rsz / 2) + (lsz / 2) * ((morersz + 1) / 2 - (rsz + 1) / 2);
            ans += tot * val;
        }

        seen.insert(idx);
    }

    //1: max(range) is fine
    //2: second_max(range) is fine
    //3: replace max(range) with max(l, r)
    //4: replace second_max(range) with casework4(range)
    //6: replace second_max(range) with casework6(range)

    //3
    for (int i = 0; i < n - 2; i++) ans += max(a[i], a[i + 2]) - max({a[i], a[i + 1], a[i + 2]});

    //4
    for (int i = 0; i < n - 3; i++) {
        int best1 = -1, best2 = -1, best3 = -1;
        for (int j = i; j < i + 4; j++) {
            setmx(best3, a[j]);
            if (best3 > best2) swap(best2, best3);
            if (best2 > best1) swap(best1, best2);
        }

        int l = -1, r = -1;
        for (int j = 0; j < 4; j++) {
            if (l == -1 and a[i + j] == best1) l = j;
            else if (r == -1 and a[i + j] == best2) r = j;
        }
        if (l > r) swap(l, r);
        
        ans -= best2;
        if (l == 0 and r == 2) ans += best3;
        else if (l == 1 and r == 2) ans += best3;
        else if (l == 1 and r == 3) ans += best3;
        else ans += best2;
    }
    
    //6
    for (int i = 0; i < n - 5; i++) {
        int best1 = -1, best2 = -1, best3 = -1;
        for (int j = i; j < i + 6; j++) {
            setmx(best3, a[j]);
            if (best3 > best2) swap(best2, best3);
            if (best2 > best1) swap(best1, best2);
        }

        int l = -1, r = -1;
        for (int j = 0; j < 6; j++) {
            if (l == -1 and a[i + j] == best1) l = j;
            else if (r == -1 and a[i + j] == best2) r = j;
        }
        if (l > r) swap(l, r);

        ans -= best2;
        if (l == 1 and r == 3) ans += best3;
        else if (l == 1 and r == 4) ans += best3;
        else if (l == 2 and r == 4) ans += best3;
        else ans += best2;
    }

    cout << ans << "\n";

	return 0;
}
