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

template <class T> void setmn(T &a, T b) {
    a = min(b, a);
    return;
}

template <class T> void setmx(T &a, T b) {
    a = max(b, a); 
    return;
}

int t, curidx = 0, cnt[3] = {0, 0, 0};
string cur, fail[6] = {"ab", "ac", "ba", "bc", "ca", "cb"};
string psbl[105];

int getcnt(string& a, string& b) {
    int sz = b.size(), idx = 0, res = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] == b[idx]) idx++;
        if (idx == sz) {
            res++;
            idx = 0;
        }
    }
    return res;
}

void dfs(int len) {
    for (char c = 'a'; c <= 'c'; c++) {
        cur += c;
        cnt[c - 'a']++;

        int mx = *max_element(cnt, cnt + 3);
        bool works = true;

        if (len == 1) works = true;
        else if (len == 2 or len == 3) works = (mx == 1);
        else if (len == 4) works = false;
        else {
            if (mx != 2) works = false;
            for (string& s : fail) if (getcnt(cur, s) > 1) works = false;
        }

        if (works) {
            psbl[curidx] = cur;
            curidx++;
        }

        if (len < 6) dfs(len + 1);

        cur.pop_back();
        cnt[c - 'a']--;
    }

    return;
}

void subcase() {
    int n;
    ll ans = 0;
    string s;
    cin >> n >> s;

    for (int i = 0; i < 105; i++) {
        ll cur = getcnt(s, psbl[i]), sz = psbl[i].size();
        setmx(ans, cur * cur * sz);
    }
    cout << ans << "\n";

	return;
}

int main() {
    //freopen("city.in", "r", stdin);
    //freopen("city.out", "w", stdout);

	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    dfs(1);

	cin >> t;

	for (int i = 0; i < t; i++) subcase();

	return 0;
}
