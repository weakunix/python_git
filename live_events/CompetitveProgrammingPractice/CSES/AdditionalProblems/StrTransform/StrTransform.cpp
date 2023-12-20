#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <utility>
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

const int N = 1e6 + 1;

int n, nxtidx[28], idx[N], cur;
string s, ans;

int main() {
    memset(nxtidx, 0, sizeof(nxtidx));

    cin >> s;
    n = s.size();

    for (int i = 0; i < n; i++) {
        if (s[i] == '#') {
            nxtidx[1]++;
            cur = i;
        }
        else nxtidx[(s[i] - 'a') + 2]++;
    }
    for (int i = 1; i < 28; i++) nxtidx[i] += nxtidx[i - 1];

    for (int i = 0; i < n; i++) {
        int c = (s[i] == '#' ? 0 : (s[i] - 'a') + 1);
        idx[i] = nxtidx[c];
        nxtidx[c]++;
    }
    for (int i = 0; i < n - 1; i++) {
        cur = idx[cur];
        ans += s[cur];
    }

    reverse(all(ans));
    cout << ans << "\n";

	return 0;
}
