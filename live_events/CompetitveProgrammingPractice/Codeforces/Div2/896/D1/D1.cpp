#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
#include <map>
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

const int N = 2e5, L = 31;

int t;
map<int, int> lgmap;

void subcase() {
    int n, arr[N], r[N], g[N];
    ll tar = 0;
    cin >> n;
    map<int, int> give, receive;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        tar += arr[i];
    }

    if (tar % n) {
        cout << "No\n";
        return;
    }
    tar /= n;

    for (int i = 0; i < n; i++) {
        if (arr[i] == tar) {
            g[i] = -1;
            r[i] = -1;
            continue;
        }

        int x = abs(tar - arr[i]), cur = 0;
        bool giver = (arr[i] > tar);
        while (x % 2 == 0) {
            cur++;
            x /= 2;
        }

        x++;
        if (lgmap.count(x) == 0) {
            cout << "No\n";
            return;
        }

        x = cur + lgmap[x];

        if (giver) {
            g[i] = x;
            r[i] = cur;
        }
        else {
            g[i] = cur;
            r[i] = x;
        }
    }

    for (int i = 0; i < n; i++) {
        if (g[i] == -1) continue;
        give[g[i]]++;
        receive[r[i]]++;
    }
    
    for (auto u : give) {
        if (u.second != receive[u.first]) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    for (int i = 0; i < L; i++) lgmap[1 << i] = i;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
