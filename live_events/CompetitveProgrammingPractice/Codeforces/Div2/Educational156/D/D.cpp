#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
#include <set>
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

const int N = 3e5 + 5, modval = 998244353;

int n, m, arr[N];
ll fact[N], invfact[N], ans = 1;
set<simps> ranges;

ll pw(ll a, int b) {
    ll res = 1;
    while (b) {
        if (b & 1) res = res * a % modval;
        a = a * a % modval;
        b >>= 1;
    }
    return res;
}

void addrange(simps rng) {
    ranges.insert(rng);
    if (rng.first != 0) ans = ans * fact[rng.second] % modval * invfact[rng.first - 1] % modval;
    return;
}

void remrange(simps rng) {
    ranges.erase(rng);
    if (rng.first != 0) ans = ans * invfact[rng.second] % modval * fact[rng.first - 1] % modval;
    return;
}

void printans() {
    if (ranges.size() and ranges.begin()->first == 0) cout << "0\n";
    else cout << ans << "\n";
    return;
}

void firstcase() {
    int st = -1;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 1) {
            if (st == -1) st = i;
        }
        else {
            if (st != -1) addrange({st, i - 1});
            st = -1;
        }
    }
    if (st != -1) addrange({st, n - 1});

    return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    fact[0] = 1;
    invfact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % modval;
        invfact[i] = pw(fact[i], modval - 2);
    }

	cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        char c;
        cin >> c;
        arr[i] = c == '?' ? 1 : (c == '<' ? 0 : 2);
    }

    firstcase();
    printans();

    for (int i = 0; i < m; i++) {
        int idx, intc;
        char c;
        cin >> idx >> c;
        idx--;
        intc = c == '?' ? 1 : (c == '<' ? 0 : 2);

        if (intc == 1) {
            if (arr[idx] != 1) {
                auto it = ranges.lower_bound({idx, 1e9});
                simps l = {-1e9, -1e9}, r = {1e9, 1e9};
                
                if (it != ranges.end()) r = *it;
                if (it != ranges.begin()) {
                    it--;
                    l = *it;
                }

                simps nw = {idx, idx};

                if (l.second == idx - 1) {
                    remrange(l);
                    nw.first = l.first;
                }

                if (r.first == idx + 1) {
                    remrange(r);
                    nw.second = r.second;
                }

                addrange(nw);
            }
        }
        else {
            if (arr[idx] == 1) {
                auto it = ranges.lower_bound({idx, 1e9});
                simps cur;
                it--;
                cur = *it;
                remrange(cur);
                
                if (cur.first == idx and cur.first != cur.second) {
                    cur.first++;
                    addrange(cur);
                }
                else if (cur.second == idx and cur.first != cur.second) {
                    cur.second--;
                    addrange(cur);
                }
                else if (cur.first != cur.second) {
                    simps l = {cur.first, idx - 1}, r = {idx + 1, cur.second};
                    addrange(l);
                    addrange(r);
                }
            }
        }

        printans();

        arr[idx] = intc;
    }

	return 0;
}
