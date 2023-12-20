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

const int N = 1e6 + 1, L = 21;

int n, pwp[L][N], pwc[L][N];
string s;

void genfirst() {
    vector<int> cnt[27];
    for (int i = 0; i < n; i++) cnt[s[i] == '#' ? 0 : (s[i] - 'a') + 1].push_back(i);

    int cur = -1, idx = 0;
    for (int i = 0; i < 27; i++) {
        if (cnt[i].empty()) continue;
        cur++;
        for (int j : cnt[i]) {
            pwp[0][idx] = j;
            idx++;
            pwc[0][j] = cur;
        }
    }

    return;
}

void genpw() {
    for (int i = 1; i < L; i++) {
        vector<simps> cnt[N]; //segfault
        for (int j = 0; j < n; j++) {
            int cur = ((pwp[i - 1][j] - (1 << (i - 1))) % n + n) % n;
            cnt[pwc[i - 1][cur]].push_back({cur, pwc[i - 1][pwp[i - 1][j]]});
        }

        int cur = -1, idx = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < cnt[j].size(); k++) {
                cur += (k == 0 or cnt[j][k].second != cnt[j][k - 1].second);
                pwp[i][idx] = cnt[j][k].first;
                idx++;
                pwc[i][cnt[j][k].first] = cur;
            }
        }
    }

    return;
}

int main() {
    cin >> s;
    s += '#';
    n = s.size();

    genfirst();
    genpw();

    for (int i = 0; i < n; i++) cout << s[(pwp[L - 1][i] + n - 1) % n];
    cout << "\n";

	return 0;
}
