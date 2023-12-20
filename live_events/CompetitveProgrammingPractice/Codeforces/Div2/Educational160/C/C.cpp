#include <iostream>
#include <string>
#include <cstring>
#include <vector>
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

int m;
vector<int> cnt(31);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    cin >> m;
    for (int i = 0; i < m; i++) {
        int t, v;
        cin >> t >> v;
        if (t == 1) {
            cnt[v]++;
            continue;
        }

        int cur = 0;
        bool works = true;
        vector<int> curcnt = cnt;
        while (v) {
            if (v & 1) {
                if (curcnt[cur] == 0) {
                    works = false;
                    break;
                }
                curcnt[cur]--;
            }
            curcnt[cur + 1] += curcnt[cur] / 2;
            v >>= 1;
            cur++;
        }
        cout << (works ? "YES\n" : "NO\n");
    }

	return 0;
}
