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

const int N = 1e5;

int n, m, cnt[N], ac = 0, wa = 0;

int main() {
    clr(cnt, 0);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int p;
        string s;
        cin >> p >> s;
        p--;

        if (cnt[p] == -1) continue;

        if (s == "AC") {
            ac++;
            wa += cnt[p];
            cnt[p] = -1;
        }
        else cnt[p]++;
    }

    cout << ac << " " << wa << "\n";

	return 0;
}
