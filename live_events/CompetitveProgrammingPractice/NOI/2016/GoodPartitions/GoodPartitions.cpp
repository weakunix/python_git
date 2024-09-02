#include <iostream>
#include <cstdio>
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
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define pb push_back
#define bp pop_back
#define lb lower_bound
#define ub upper_bound
#define mkpr make_pair
#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define clr(arr, val) memset(arr, val, sizeof(arr))

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

const int N = 3e4 + 2, L = 16;
int lg[N];

struct SuffixArr {
    int n, k;
    string s;
    vector<int> p[L], c[L], st[L];

    SuffixArr() : n(0), k(0), s("") {}

    SuffixArr(string _s) : n(_s.size() + 1), k(0), s(_s + '$') {
        buildfirst();
        while ((1 << k) < n) {
            k++;
            buildnxt();
        }
        buildlcp();
        return;
    }

    ~SuffixArr() {}

    void buildfirst() {
        p[0].resize(n);
        c[0].resize(n);

        vector<int> cnt[27];
        for (int i = 0; i < n; i++) {
            if (s[i] == '$') cnt[0].pb(i);
            else cnt[s[i] - 'a' + 1].pb(i);
        }

        int idx = 0, cur = 0;
        for (int i = 0; i < 27; i++) {
            if (cnt[i].empty()) continue;
            for (int j : cnt[i]) {
                p[0][idx] = j;
                idx++;
                c[0][j] = cur;
            }
            cur++;
        }

        return;
    }

    void buildnxt() {
        p[k].resize(n);
        c[k].resize(n);

        simps prvc[N];
        vector<vector<int>> cnt1(n), cnt2(n);
        for (int i = 0; i < n; i++) {
            prvc[i] = {c[k - 1][i], c[k - 1][(i + (1 << (k - 1))) % n]};
            cnt2[prvc[i].second].pb(i);
        }
        for (int i = 0; i < n; i++) for (int j : cnt2[i]) cnt1[prvc[j].first].pb(j);

        int idx = 0, cur = -1;
        for (int i = 0; i < n; i++) {
            if (cnt1[i].empty()) continue;
            for (int j = 0; j < cnt1[i].size(); j++) {
                if (j == 0 or prvc[cnt1[i][j]].second != prvc[cnt1[i][j - 1]].second) cur++;
                p[k][idx] = cnt1[i][j];
                idx++;
                c[k][cnt1[i][j]] = cur;
            }
        }

        return;
    }

    void buildlcp() {
        st[0].resize(n);

        int cur = 0;
        for (int i = 0; i < n - 1; i++) {
            while (s[i + cur] == s[p[k][c[k][i] - 1] + cur]) cur++;
            st[0][c[k][i]] = cur;
            cur = max(cur - 1, 0);
        }

        for (int i = 1; (1 << i) <= n; i++) {
            st[i].resize(n);
            for (int j = 0; j + (1 << i) <= n; j++) st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
        }

        return;
    }

    int getlcp(int a, int b) {
        a = c[k][a]; b = c[k][b];
        if (a > b) swap(a, b);
        a++;
        int len = lg[b - a + 1];
        return min(st[len][a], st[len][b - (1 << len) + 1]);
    }
};

int t;

void subcase() {
    int n;
    string s;
    cin >> s;
    n = s.size();

    SuffixArr sa(s);
    reverse(all(s));
    SuffixArr revsa(s);

    ll pfx[N], revpfx[N];
    clr(pfx, 0);
    clr(revpfx, 0);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j + i < n; j += i) {
            int x = min(revsa.getlcp(n - j - 1, n - (j + i) - 1), i);
            int y = min(sa.getlcp(j, j + i), i);
            if (x + y - i < 1) continue;

            int l = j - x + 1, r = l + x + y - i;
            pfx[l]++;
            pfx[r]--;

            r = j + i + y - 1;
            l = r - (x + y - i);
            revpfx[r]++;
            revpfx[l]--;
        }
    }

    for (int i = 1; i < n; i++) pfx[i] += pfx[i - 1];
    for (int i = n - 2; i >= 0; i--) revpfx[i] += revpfx[i + 1];
    
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) ans += revpfx[i] * pfx[i + 1];
    cout << ans << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    lg[1] = 0;
    for (int i = 2; i < N; i++) lg[i] = lg[i / 2] + 1;

	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
