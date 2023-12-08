#include <iostream>
#include <cstdio>
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

const int N = 2e5 + 1, L = 18;

int n, len = 0, sz[N], sid[N], pwp[L][N], pwc[L][N], p[N], c[N], lcp[N], prv[N], nxt[N];
ll ans[N];
string s;

void genfirst() {
    vector<int> cnt[28];

    for (int i = 0; i < len; i++) cnt[s[i] == '#' ? 0 : (s[i] == '$' ? 1 : (s[i] - 'a') + 2)].push_back(i);

    int cur = -1, idx = 0;
    for (int i = 0; i < 28; i++) {
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
    for (int i = 1; (1 << i) <= len; i++) {
        vector<simps> cnt[N];

        for (int j = 0; j < len; j++) {
            int cur = (pwp[i - 1][j] + len - (1 << (i - 1))) % len;
            cnt[pwc[i - 1][cur]].push_back({cur, pwc[i - 1][pwp[i - 1][j]]});
        }

        int cur = -1, idx = 0;
        for (int j = 0; j < len; j++) {
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
        if (not (len & (1 << i))) continue;

        vector<simps> cnt[N];

        for (int j = 0; j < len; j++) {
            int cur = (p[j] + len - (1 << i)) % len;
            cnt[pwc[i][cur]].push_back({cur, c[p[i]]});
        }

        int cur = -1, idx = 0;
        for (int j = 0; j < len; j++) {
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

void kasai() {
    int cur = 0;

    for (int i = 0; i < len; i++) {
        if (c[i] == len - 1) {
            cur = 0;
            continue;
        }
        if (cur > 0) cur--;
        
        int j = p[c[i] + 1];
        while ((i + cur < len and j + cur < len) and s[i + cur] == s[j + cur]) cur++;
        lcp[j] = cur;
    }

    return;
}

void genprv() {
    int cur = 0;
    for (int i = n + 1; i < len; i++) {
        if (sid[p[i]] != sid[p[i - 1]]) cur = lcp[p[i]];
        cur = min(lcp[p[i]], cur);
        prv[i] = cur;
    }
    return;
}

void gennxt() {
    int cur = 0;
    for (int i = len - 1; i > n; i--) {
        nxt[i] = cur;
        if (sid[p[i - 1]] != sid[p[i]]) cur = lcp[p[i]];
        cur = min(lcp[p[i]], cur);
    }
    return;
}

int main() {
    freopen("standingout.in", "r", stdin);
    freopen("standingout.out", "w", stdout);

    memset(c, 0, sizeof(c));
    for (int i = 0; i < N; i++) p[i] = i;

    cin >> n;
    for (int i = 0; i < n; i++) {
        string cur;
        cin >> cur;
        for (int j = len; j < len + cur.size(); j++) {
            sid[j] = i;
            sz[j] = len + cur.size() - j;
        }
        sid[len + cur.size()] = -1;
        len += cur.size() + 1;
        s += cur + '$';
    }
    sid[len] = -1;
    s += '#';
    len++;

    genfirst();
    genpw();
    genfull();
    kasai();
    genprv();
    gennxt();

    for (int i = n + 1; i < len; i++) ans[sid[p[i]]] += max(sz[p[i]] - max({prv[i], nxt[i], lcp[p[i]]}), 0);
    for (int i = 0; i < n; i++) cout << ans[i] << "\n";

    //for (int i = 0; i < len; i++) cout << sid[p[i]] << " " << s.substr(p[i], len - p[i]) << " " << sz[p[i]] << " " << lcp[p[i]] << " " << prv[i] << " " << nxt[i] << "\n"; //DEBUG

	return 0;
}
