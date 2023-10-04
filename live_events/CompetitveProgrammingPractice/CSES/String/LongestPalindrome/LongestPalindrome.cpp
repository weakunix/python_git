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

const int N = 2e6 + 5;

int n, sz[N], l = -1, r = -1;
simps ans = {0, -1};
string s;

void prep() {
    string res = "$";
    for (char c : s) {
        res += c;
        res += '$';
    }
    s = res;
    return;
}

int main() {
    cin >> s;
    prep();
    n = s.size();
    for (int i = 0; i < n; i++) {
        if (i > r) {
            l = i;
            r = i;
            while ((l > 0 and r < n) and s[l - 1] == s[r + 1]) {
                l--;
                r++;
            }
            sz[i] = r - l + 1;
            continue;
        }
        sz[i] = sz[l + r - i];
        if (sz[i] / 2 < r - i) continue;
        if (sz[i] / 2 > r - i) {
            sz[i] = 2 * (r - i) + 1;
            continue;
        }
        l = i - sz[i] / 2;
        r = i + sz[i] / 2;
        while ((l > 0 and r < n) and s[l - 1] == s[r + 1]) {
            l--;
            r++;
        }
        sz[i] = r - l + 1;
    }
    for (int i = 0; i < n; i++) ans = max(make_pair(sz[i], i), ans);
    for (int i = ans.second - ans.first / 2; i <= ans.second + ans.first / 2; i++) {
        if (s[i] != '$') cout << s[i];
    }
    cout << "\n";
	return 0;
}
