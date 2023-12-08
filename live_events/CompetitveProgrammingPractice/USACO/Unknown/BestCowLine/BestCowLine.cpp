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

const int N = 6e4 + 2, L = 17;

int n, pwp[L][N], pwc[L][N];
string s, ans;

void genfirst() {
    vector<int> cnt[27];
    cnt[0] = {n, 2 * n + 1};
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s += c;
        int cur = (c - 'A') + 1;
        cnt[cur].push_back(i);
        cnt[cur].push_back(2 * n - i);
    }

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
        vector<simps> cnt[N];

        for (int j = 0; j < 2 * n + 2; j++) {
            int cur = ((pwp[i - 1][j] - (1 << (i - 1))) % (2 * n + 2) + 2 * n + 2) % (2 * n + 2);
            cnt[pwc[i - 1][cur]].push_back({cur, pwc[i - 1][pwp[i - 1][j]]});
        }


        int cur = -1, idx = 0;
        for (int j = 0; j < 2 * n + 2; j++) {
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
    cin >> n;
    genfirst();
    genpw();

    int l = 0, r = n - 1;

    while (l <= r) {
        if (pwc[L - 1][l] < pwc[L - 1][2 * n - r]) {
            ans += s[l];
            l++;
        }
        else {
            ans += s[r];
            r--;
        }
    }

    l = 0;
    while (n >= 80) {
        cout << ans.substr(l, 80) << "\n";
        l += 80;
        n -= 80;
    }
    cout << ans.substr(l, n) << "\n";

	return 0;
}
