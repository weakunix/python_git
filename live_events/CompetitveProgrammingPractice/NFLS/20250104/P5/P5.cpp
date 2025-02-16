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

const int X = 1440, Y = 101;

int n, m, bots[X][Y], botsy[Y], jobs[X][Y], anscnt;
ll ansscore;

int main() {
    while (cin >> n) {
        anscnt = 0;
        ansscore = 0;
        clr(bots, 0);
        clr(botsy, 0);
        clr(jobs, 0);

        cin >> m;
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            bots[x][y]++;
        }
        for (int i = 0; i < m; i++) {
            int x, y;
            cin >> x >> y;
            jobs[x][y]++;
        }

        for (int i = X - 1; i >= 0; i--) {
            map<int, int> psbl;
            for (int j = Y - 1; j >= 0; j--) {
                botsy[j] += bots[i][j];
                if (botsy[j]) psbl[j] = botsy[j];
                while (jobs[i][j] and psbl.size()) {
                    anscnt++;
                    ansscore += 500 * i + 2 * j;
                    int cur = psbl.begin()->first;
                    botsy[cur]--;
                    psbl[cur]--;
                    if (not psbl[cur]) psbl.erase(cur);
                    jobs[i][j]--;
                }
            }
        }

        cout << anscnt << " " << ansscore << "\n";
    }

	return 0;
}
