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

const int N = 2e5 + 10, Q = 1e5;

struct SA {
    int n;
    string s;
    vector<int> p, c;

    SA() : n(0), s("") {}

    SA(string _s) : n(_s.size() + 2), s("%" + _s + "$") {
        p.resize(n);
        c.resize(n);
        buildfirst();
        for (int i = 0; (1 << i) < n; i++) buildnxt(i);
        return;
    }

    ~SA() {}

    int getchar(char c) {
        if (c == '$') return 0;
        if (c == '%') return 27;
        return c - 'a' + 1;
    }

    void buildfirst() {
        int idx[28];

        clr(idx, 0);
        
        for (char c : s) idx[getchar(c)]++;

        for (int i = 1; i < 28; i++) idx[i] += idx[i - 1];

        for (int i = 0; i < n; i++) {
            idx[getchar(s[i])]--;
            p[idx[getchar(s[i])]] = i;
        }

        int cur = 0;
        c[p[0]] = 0;

        for (int i = 1; i < n; i++) {
            cur += (s[p[i]] != s[p[i - 1]]);
            c[p[i]] = cur;
        }

        return;
    }

    void buildnxt(int k) {
        int idx[N];
        vector<int> prvp(n), nwc(n);

        clr(idx, 0);

        for (int i = 0; i < n; i++) prvp[i] = (p[i] + n - (1 << k)) % n;

        for (int i = 0; i < n; i++) idx[c[prvp[i]]]++;

        for (int i = 1; i < n; i++) idx[i] += idx[i - 1];

        for (int i = n - 1; i >= 0; i--) {
            idx[c[prvp[i]]]--;
            p[idx[c[prvp[i]]]] = prvp[i];
        }

        int cur = 0;
        nwc[p[0]] = 0;

        for (int i = 1; i < n; i++) {
            cur += (c[p[i]] != c[p[i - 1]] or c[(p[i] + (1 << k)) % n] != c[(p[i - 1] + (1 << k)) % n]);
            nwc[p[i]] = cur;
        }

        swap(c, nwc);

        return;
    }
};

struct BIT {
    int n;
    vector<int> bit;

    BIT() : n(0) {}
    
    BIT(int _n) : n(_n) {
        bit.resize(n + 1);
        return;
    }

    ~BIT() {}

    void set(int idx, int c) {
        for (; idx <= n; idx += idx & (-idx)) bit[idx] += c;
        return;
    }

    int get(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & (-idx)) res += bit[idx];
        return res;
    }

    int qry(int l, int r) {
        return get(r) - get(l - 1);
    }
};

struct Manacher {
    int n;
    string s;
    vector<int> p;
    
    Manacher() : n(0), s("") {}

    Manacher(string _s) : n(2 * _s.size() + 1), s("%") {
        p.resize(n + 2);
        for (char c : _s) {
            s += '#';
            s += c;
        }
        s += "#$";
        build();
        return;
    }

    ~Manacher() {}

    void build() {
        int l = 1, r = 1;
        for (int i = 1; i <= n; i++) {
            p[i] = max(0, min(r - i, p[l + (r - i)]));
            while (s[i - p[i]] == s[i + p[i]]) p[i]++;
            if (i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
        }

        for (int i = 1; i <= n; i++) {
            char a = s[i - p[i]], b = s[i + p[i]];
            if (a == '%') p[i] = 0;
            else if (b == '$') p[i] = 0;
            else {
                if (a < b) p[i] = 0;
            }
        }

        return;
    }

    int get(int idx) {
        return (p[2 * idx + 1] - 1) / 2;
    }
};

int t, n, q, ans[Q], remcnt[N];
simps arr[Q];
string s;
vector<int> qord[N], addord[N];

void subcase() {
    clr(ans, 0);
    clr(remcnt, 0);
    for (int i = 0; i < N; i++) {
        qord[i].clear();
        addord[i].clear();
    }

    cin >> n >> q >> s;
    for (int i = 0; i < q; i++) {
        cin >> arr[i].first >> arr[i].second;
        qord[arr[i].first].pb(i);
    }

    Manacher man(s);
    
    s += '%';
    for (int i = n - 1; i >= 0; i--) s += s[i];

    SA sa(s);
    BIT bit[2] = {BIT(2 * n), BIT(2 * n)}, palbit(n);

    for (int i = 2 * n; i > 0; i--) {
        int x = sa.p[i];
        if (x >= n) {
            x--;
            bit[x % 2].set(x, 1);
        }
        else {
            for (int j : qord[x]) {
                int r = arr[j].second;
                ans[j] = bit[x % 2].qry(2 * n - (x + 2 * r - 1) + 1, 2 * n - x + 1);
            }
        }
    }


    for (int i = 1; i < n; i++) {
        int cur = man.get(i);
        if (cur == 0) continue;
        addord[i - cur + 1].pb(i);
        remcnt[i]++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j : addord[i]) palbit.set(j, 1);
        for (int j : qord[i]) {
            int r = arr[j].second;
            ans[j] -= palbit.qry(i, i + r - 1);
        }
        palbit.set(i, -remcnt[i]);
    }

    for (int i = 0; i < q; i++) cout << ans[i] << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
