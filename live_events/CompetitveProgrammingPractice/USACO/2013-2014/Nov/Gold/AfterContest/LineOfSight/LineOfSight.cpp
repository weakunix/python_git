#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

const double pi = 3.14159265359;

int n, r;
ll ans = 0;
priority_queue<double> alradd;
priority_queue<pair<double, double>> toadd;

int main() {
    freopen("sight.in", "r", stdin);
    freopen("sight.out", "w", stdout);

    cin >> n >> r;
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        
        double theta = atan2(y, x), alpha = acos(r / sqrt(x * x + y * y));

        double enter = theta - alpha;
        double exit = theta + alpha;

        if (x <= -r) {
            if (y < 0) {
                enter += 2 * pi;
                exit += 2 * pi;
            }
            alradd.push(-exit + 2 * pi);
            toadd.push({-enter, -exit});
            continue;
        }

        toadd.push({-enter, -exit});
    }

    while (toadd.size()) {
        while (alradd.size() and alradd.top() > toadd.top().first) alradd.pop();
        ans += alradd.size();
        alradd.push(toadd.top().second);
        toadd.pop();
    }

    cout << ans << "\n";
	return 0;
}
