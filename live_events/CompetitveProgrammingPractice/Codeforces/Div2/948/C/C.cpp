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

int t, n;
vector<ll> vals;
set<ll> allvals;
map<ll, int> ans;
map<ll, map<ll, int>> pf;

void getpf(ll num) {
    ll ognum = num;
    for (ll i = 2; i * i <= num; i++) {
        while (num % i == 0) {
            pf[ognum][i]++;
            num /= i;
        }
    }
    if (num > 1) pf[ognum][num]++;
    return;
}

int solve(ll num) {
    if (ans.count(num)) return ans[num];

    int cnt = 0;
    ll curlcm = 1;
    vector<ll> nxt;

    for (ll i : vals) {
        if (i >= num) break;

        bool works = true;
        for (auto& u : pf[i]) {
            if (not pf[num].count(u.first) or u.second > pf[num][u.first]) {
                works = false;
                break;
            }
        }
        if (not works) continue;

        nxt.pb(i);
        curlcm = lcm(i, curlcm);
        cnt++;
    }

    if (not cnt) {
        ans[num] = 0;
        return 0;
    }

    if (not allvals.count(curlcm)) {
        ans[num] = cnt;
        return cnt;
    }

    if (curlcm < num) {
        ans[num] = solve(curlcm);
        return ans[num];
    }

    for (auto& u : pf[num]) {
        curlcm = 1;
        int curcnt = 0;

        for (ll i : nxt) {
            if (pf[i].count(u.first) and u.second == pf[i][u.first]) continue;
            curcnt++;
            curlcm = lcm(i, curlcm);
        }

        if (not allvals.count(curlcm)) {
            setmx(ans[num], curcnt);
            continue;
        }

        setmx(ans[num], solve(curlcm));
    }

    return ans[num];
}

void subcase() {
    vals.clear();
    allvals.clear();
    ans.clear();

    cin >> n;
    vals.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> vals[i];
        allvals.insert(vals[i]);
        if (not pf.count(vals[i])) getpf(vals[i]);
    }
    sort(all(vals));

    ll totlcm = 1;
    for (ll i : vals) {
        totlcm = lcm(i, totlcm);
        if (totlcm > vals.back()) break;
    }

    if (totlcm > vals.back()) {
        cout << n << "\n";
        return;
    }

    cout << solve(vals.back()) << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
