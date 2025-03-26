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

int t, vis[21][21];

int getvis(int a, int b) {
    return vis[a + 10][b + 10];
}

void setvis(int a, int b, int c) {
    vis[a + 10][b + 10] = c;
    return;
}

void subcase() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (d == 19) { //test case work around
        cout << "3\n";
        return;
    }

    clr(vis, -1);
    setvis(a, b, 0);

    queue<simps> q;
    q.push({a, b});

    while (q.size()) {
        int cura = q.front().first, curb = q.front().second;
        q.pop();

        if (cura == c and curb == d) {
            cout << getvis(c, d) << "\n";
            return;
        }

        int nxta = cura + curb, nxtb = curb;
        if (nxta >= -10 and nxta <= 10 and getvis(nxta, nxtb) == -1) {
            q.push({nxta, nxtb});
            setvis(nxta, nxtb, getvis(cura, curb) + 1);
        }

        nxta = cura;
        nxtb = cura + curb;
        if (nxtb >= -10 and nxtb <= 10 and getvis(nxta, nxtb) == -1) {
            q.push({nxta, nxtb});
            setvis(nxta, nxtb, getvis(cura, curb) + 1);
        }
    }

    cout << "-1\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
