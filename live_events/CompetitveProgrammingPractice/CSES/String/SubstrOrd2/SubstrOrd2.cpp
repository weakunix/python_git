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

const int N = 1e5 + 1, L = 17;

int n, pwp[L][N], pwc[L][N], p[N], c[N], lcp[N], seg[4 * N], lzinc[4 * N];
bool lzclear[4 * N];
ll k;
string s;

void genfirst() {
    vector<int> cnt[27];

    for (int i = 0; i < n; i++) cnt[s[i] == '$' ? 0 : (s[i] - 'a') + 1].push_back(i);

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

void kasai() {
    int len = 0;

    for (int i = 0; i < n; i++) {
        if (len > 0) len--;
        if (c[i] == n - 1) {
            len = 0;
            continue;
        }

        int cur = p[c[i] + 1];
        while ((i + len < n and cur + len < n) and s[i + len] == s[cur + len]) len++;
        lcp[cur] = len;
    }

    return;
}

void prop(int node, int l, int r) {
    if (l < r) {
        if (lzclear[node]) {
            lzclear[2 * node] = true;
            lzinc[2 * node] = 0;
            lzclear[2 * node + 1] = true;
            lzinc[2 * node + 1] = 0;
        }
        lzinc[2 * node] += lzinc[node];
        lzinc[2 * node + 1] += lzinc[node];
    }

    if (lzclear[node]) seg[node] = 0;
    seg[node] += (r - l + 1) * lzinc[node];
    lzclear[node] = false;
    lzinc[node] = 0;
    return;
}

void clearseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lzinc[node] = 0;
        lzclear[node] = true;
        prop(node, l, r);
        return;
    }
    prop(node, l, r);
    int mid = l + (r - l) / 2;
    clearseg(2 * node, l, mid, a, b);
    clearseg(2 * node + 1, mid + 1, r, a, b);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

void incseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return;
    if (l >= a and r <= b) {
        lzinc[node]++;
        prop(node, l, r);
        return;
    }
    prop(node, l, r);
    int mid = l + (r - l) / 2;
    incseg(2 * node, l, mid, a, b);
    incseg(2 * node + 1, mid + 1, r, a, b);
    seg[node] = seg[2 * node] + seg[2 * node + 1];
    return;
}

ll getseg(int node, int l, int r, int a, int b) {
    if (l > b or r < a) return 0;
    prop(node, l, r);
    if (l >= a and r <= b) return seg[node];
    int mid = l + (r - l) / 2;
    return getseg(2 * node, l, mid, a, b) + getseg(2 * node + 1, mid + 1, r, a, b);
}

int main() {
    memset(c, 0, sizeof(c));
    for (int i = 0; i < N; i++) p[i] = i;
    memset(seg, 0, sizeof(seg));
    memset(lzinc, 0, sizeof(lzinc));
    memset(lzclear, false, sizeof(lzclear));

    cin >> s >> k;
    s += '$';
    n = s.size();

    genfirst();
    genpw();
    genfull();
    kasai();

    n--;
    k = (ll) n * (n + 1) / 2 - k + 1;
    for (int i = n; i > 0; i--) {
        int curcnt = getseg(1, 0, n, lcp[p[i]], n - p[i] - 1) + n - p[i] - lcp[p[i]];
        if (curcnt < k) {
            k -= curcnt;
            clearseg(1, 0, n, lcp[p[i]], n);
            incseg(1, 0, n, 0, lcp[p[i]] - 1);
            continue;
        }
        for (int j = n - p[i] - 1; j >= lcp[p[i]]; j--) {
            curcnt = getseg(1, 0, n, j, j) + 1;
            if (curcnt < k) {
                k -= curcnt;
                continue;
            }
            cout << s.substr(p[i], j + 1) << "\n";
            return 0;
        }
    }

    assert(false);

	return 0;
}
