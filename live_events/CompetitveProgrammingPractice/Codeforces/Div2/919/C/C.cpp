#include <iostream>
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
#include <numeric>
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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t;

void subcase() {
    int n, ans = 0;
    vector<int> arr;

    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    for (int i = 1; i <= n; i++) {
        if (n % i) continue;
        if (i == n) {
            ans++;
            continue;
        }

        vector<ll> rems;
        for (int j = 0; j < n; j += i) {
            rems.push_back(0);
            for (int k = j; k < j + i; k++) rems.back() += arr[k];
        }
        sort(all(rems));

        ll g = 0;
        for (int j = 1; j < rems.size(); j++) {
            ll cur = rems[j] - rems[j - 1];
            if (cur == 0) continue;
            if (not g) g = cur;
            else g = gcd(g, cur);
        }

        for (int j = 2; j <= n; j++) {
            if (g % j) continue;
            vector<vector<int>> cur;
            for (int k = 0; k < n; k += i) {
                cur.push_back({});
                for (int l = k; l < k + i; l++) cur.back().push_back(arr[l] % j);
                sort(all(cur.back()));
            }
            bool works = true;
            for (int k = 0; k < cur[0].size(); k++) {
                for (int l = 0; l < cur.size(); l++) {
                    if (cur[l][k] != cur[0][k]) {
                        works = false;
                        break;
                    }
                }
                if (not works) break;
            }
            if (works) {
                ans++;
                break;
            }
        }
    }

    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
