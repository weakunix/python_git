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

int n;
vector<string> alls;
map<string, int> cnt, seen;

bool cmp(string& a, string& b) {
    if (cnt[a] == cnt[b]) return seen[a] < seen[b];
    return cnt[a] > cnt[b];
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        bool leadzero = true;
        string og, s;
        cin >> og;
        for (char c : og) {
            if (c == '+') continue;
            if (c == '-') {
                s += c;
                continue;
            }
            if (leadzero and c == '0') continue;
            s += c;
            leadzero = false;
        }

        if (s == "+" or s == "-" or s.empty()) s = "0";

        if (not seen.count(s)) {
            seen[s] = i;
            alls.pb(s);
        }
        cnt[s]++;
    }

    sort(all(alls), cmp);

    if (alls.size() == 1) cout << "no\n";
    else cout << alls[0] << "\n";

	return 0;
}
