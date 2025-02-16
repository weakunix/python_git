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
#include <cmath>
#include <chrono>
#include <random>
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

mt19937 rng((int)chrono::steady_clock::now().time_since_epoch().count());

const int N = 5e5 + 5;

int getchar(char c) {
   if (c == '$') return 0;
   if (c == '#') return 1;
   return c - 'a' + 2;
}

struct SA {
    int n;
    string s;
    vector<int> p, c, lcp;

    SA() : n(0), s("") {}

    SA(string _s) : n(_s.size()), s(_s) {
        p.resize(n);
        c.resize(n);
        lcp.resize(n);
        buildfirst();
        for (int i = 0; (1 << i) < n; i++) buildnxt(i);
        buildlcp();
        return;
    }

    ~SA() {}

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

   void buildlcp() {
       int k = 0;
       for (int i = 0; i < n; i++) {
           if (c[i] == n - 1) {
               lcp[c[i]] = 0;
               k = 0;
               continue;
           }

           int j = p[c[i] + 1];
           while (s[i + k] == s[j + k]) k++;
           lcp[c[i]] = k;
           if (k) k--;
       }
       return;
   }
};

int n, q;
string s;
SA sa;

int main() {
    cin >> s;
    n = s.size();
    s += '$';
    sa = SA(s);
    
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r;
        string t;
        cin >> t >> l >> r;
        assert(l == 1 and r == n); //FIXME
        t += '#';

        SA cur(t);
        
        ll ans = (ll) t.size() * (t.size() - 1) / 2;
        for (int j : cur.lcp) ans -= j;

        int k = 0, a = 0, b = s.size() - 1;
        while (a < b) {
            int mid = a + (b - a) / 2;
            while (s[sa.p[a] + k] == t[k] and s[sa.p[b] + k] == t[k]) k++;
            
        }
    }

	return 0;
}
