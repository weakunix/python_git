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

const int N = 1e5 + 1, L = 17;

int n, pwp[L][N], pwc[L][N];
ll ans = 0;
string s;
vector<int> p, c;

void genfirst() {
    int cnt = 1, cur = 1;
    vector<int> chrcnt[26];
    for (int i = 0; i < n - 1; i++) chrcnt[s[i] - 'a'].push_back(i);
    for (int i = 0; i < 26; i++) {
        if (chrcnt[i].empty()) continue;
        for (int j : chrcnt[i]) {
            pwp[0][cur] = j;
            pwc[0][j] = cnt;
            cur++;
        }
        cnt++;
    }
    pwp[0][0] = n - 1;
    pwc[0][n - 1] = 0;
    return;
}

void genfull() {
    for (int i = 0; i < L; i++) {
        if (not (n & (1 << i))) continue;
        vector<int> oldp = p, oldc = c;
        vector<simps> cnt[N];
        for (int j = 0; j < n; j++) {
            int cur = oldp[j] - (1 << i);
            if (cur < 0) {
                cur += n;
                assert(cur >= 0);
            }
            cnt[pwc[i][cur]].push_back({oldc[oldp[j]], cur});
        }

        int cur = -1, idx = 0;
        for (int j = 0; j < n; j++) {
            if (cnt[j].empty()) continue;
            for (int k = 0; k < cnt[j].size(); k++) {
                cur += (k == 0 or cnt[j][k - 1].first != cnt[j][k].first);
                p[idx] = cnt[j][k].second;
                idx++;
                c[cnt[j][k].second] = cur;
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
        ans += len;
    }
}

int main() {
    cin >> s;
    s += '$';
    n = s.size();
    genfirst();
    p.resize(n);
    for (int i = 0; i < n; i++) p[i] = i;
    c.resize(n);

    for (int i = 1; (1 << i) <= n; i++) {
        vector<simps> cnt[N];
        for (int j = 0; j < n; j++) {
            int cur = pwp[i - 1][j] - (1 << (i - 1));
            if (cur < 0) {
                cur += n;
                assert(cur >= 0);
            }
            cnt[pwc[i - 1][cur]].push_back({pwc[i - 1][pwp[i - 1][j]], cur});
        }

        int cur = -1, idx = 0;
        for (int j = 0; j < n; j++) {
            if (cnt[j].empty()) continue;
            for (int k = 0; k < cnt[j].size(); k++) {
                cur += (k == 0 or cnt[j][k - 1].first != cnt[j][k].first);
                pwp[i][idx] = cnt[j][k].second;
                idx++;
                pwc[i][cnt[j][k].second] = cur;
            }
        }
    }

    genfull();

    kasai();

    cout << (ll) n * (n - 1) / 2 - ans << "\n";
    
    /*
    int dbg = 2;
    for (int i = 0; i < n; i++) cout << pwp[dbg][i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << pwc[dbg][i] << " ";

    for (int i = 0; i < n; i++) cout << p[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) cout << c[i] << " ";
    */
    
	return 0;
}
