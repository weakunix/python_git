#include <iostream>
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

const int N = 1e5, L = 17;

int n, pwp[L][N], pwc[L][N], p[N], c[N];

void genfirst() {
    vector<int> cnt[26];
    for (int i = 0; i < n; i++) {
        char cur;
        cin >> cur;
        cnt[cur - 'a'].push_back(i);
    }

    int cur = -1, idx = 0;
    for (int i = 0; i < 26; i++) {
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
    for (int i = 1; (1 << i) <= n; i++) {
        vector<simps> cnt[N];

        for (int j = 0; j < n; j++) {
            int cur = (pwp[i - 1][j] + n - (1 << (i - 1))) % n;
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

void genfull() {
    for (int i = 0; i < L; i++) {
        if (not (n & (1 << i))) continue;

        vector<simps> cnt[N];
        
        for (int j = 0; j < n; j++) {
            int cur = (p[j] + n - (1 << i)) % n;
            cnt[pwc[i][cur]].push_back({cur, c[p[j]]});
        }

        int cur = -1, idx = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < cnt[j].size(); k++) {
                cur += (k == 0 or cnt[j][k].second != cnt[j][k - 1].second);
                p[idx] = cnt[j][k].first;
                idx++;
                c[cnt[j][k].first] = cur;
            }
        }
    }

    return;
}

int main() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i < N; i++) p[i] = i;

    cin >> n;
    genfirst();
    genpw();
    genfull();
    cout << p[0] << "\n";
	return 0;
}
