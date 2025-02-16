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

const map<char, int> mp = {
    {'B', 0},
    {'E', 1},
    {'S', 2},
    {'I', 3},
    {'G', 4},
    {'O', 5},
    {'M', 6}
};

int n, cur[7];
ll cnt[7][7], ans = 0;

void dfs(int idx) {
    if (idx == 7) {
        bool works = false;
        if ((cur[0] + cur[1] + cur[2] + cur[2] + cur[3] + cur[1]) % 7 == 0) works = true;
        if ((cur[4] + cur[5] + cur[1] + cur[2]) % 7 == 0) works = true;
        if ((cur[6] + cur[5] + cur[5]) % 7 == 0) works = true;
        if (works) {
            ll curans = 1;
            for (int i = 0; i < 7; i++) curans *= cnt[i][cur[i]];
            ans += curans;
        }
        return;
    }

    for (int i = 0; i < 7; i++) {
        cur[idx] = i;
        dfs(idx + 1);
    }

    return;
}

int main() {
    clr(cnt, 0);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        char c;
        cin >> c >> cur;
        cur = (cur % 7 + 7) % 7;
        cnt[mp.at(c)][cur]++;
    }

    dfs(0);

    cout << ans << "\n";

	return 0;
}
