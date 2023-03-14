#include <iostream>
#include <string>
#include <vector>
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

const int modval = 1e9 + 7;

int n, m, finans = 0;
vector<int> cnt, og;
vector<ll> ans, fact, invfact;
vector<vector<bool>> diff;
map<int, int> label;

void getinvfact() {
    int pow = modval - 2;
    ll cur = fact[n];
    invfact[n] = 1;
    while (pow != 0) {
        if (pow % 2 != 0) invfact[n] = (invfact[n] * cur) % modval;
        cur = (cur * cur) % modval;
        pow /= 2;
    }
    for (int i = n - 1; i >= 0; i--) invfact[i] = (invfact[i + 1] * (i + 1)) % modval;
    return;
}

int choose(int n, int m) {
    return (((fact[n] * invfact[m]) % modval) * invfact[n - m]) % modval;
}

void setans(int idx) {
    for (int i = 1; i <= cnt[idx]; i++) ans[idx] = (ans[idx] + (fact[i] * choose(cnt[idx], i)) % modval) % modval;
    return;
}

void input() {
    map<int, int> curcnt;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            diff[i][j] = (c == 'H');
        }
    }
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < m; j++) {
            if (diff[j][i]) cur += (1 << j);
        }
        curcnt[cur]++;
    }
    n = curcnt.size();
    cnt.resize(n);
    og.resize(n);
    ans.resize(n);
    int cur = 0;
    for (auto u : curcnt) {
        label[u.first] = cur;
        og[cur] = u.first;
        cnt[cur] = u.second;
        setans(cur);
        cur++;
    }
    return;
}

bool works(int a, int b) {
    assert(a <= b);
    return (og[b] - og[a] == (og[b] ^ og[a]));
}

int main() {
    cin >> n >> m;
    fact.resize(n + 1);
    invfact.resize(n + 1);
    diff.resize(m, vector<bool>(n));
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = (fact[i - 1] * i) % modval;
    getinvfact();
    input();
    if (m == 1) {
        cout << ((ans[0] + 1) * (ans[1] + 1) - 1) % modval << "\n";
        return 0;
    }
    for (int i = n - 1; i >= 0; i--) {
        ll curans = ans[i];
        for (int j = i + 1; j < n; j++) {
            if (works(i, j)) curans = (curans + (ans[i] * ans[j]) % modval) % modval;
        }
        ans[i] = curans;
        finans = (finans + ans[i]) % modval;
    }
    cout << finans << "\n";
	return 0;
}
