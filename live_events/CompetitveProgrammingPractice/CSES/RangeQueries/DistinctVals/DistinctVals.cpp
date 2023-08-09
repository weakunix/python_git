#include <iostream>
#include <cstring>
#include <vector>
#include <utility>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

int n, q, sz, l = 0, r = -1, curans = 0;
vector<int> arr, cnt, ans;
vector<threesome> queries;
unordered_map<int, int> compmap;

bool cmp(threesome a, threesome b) {
    if (a.sec / sz == b.sec / sz) return a.third < b.third;
    return a.sec / sz < b.sec / sz;
}

int main() {
    int n, q;
    cin >> n >> q;
    sz = sqrt(n);
    arr.resize(n);
    ans.resize(q);
    queries.resize(q);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        if (compmap.count(arr[i]) == 0) compmap[arr[i]] = compmap.size();
        arr[i] = compmap[arr[i]];
    }
    cnt.resize(compmap.size());
    for (int i = 0; i < q; i++) {
        cin >> queries[i].sec >> queries[i].third;
        queries[i].first = i;
        queries[i].sec--;
        queries[i].third--;
    }
    sort(all(queries), cmp);
    for (threesome t : queries) {
        while (l > t.sec) {
            l--;
            curans += (cnt[arr[l]] == 0);
            cnt[arr[l]]++;
        }
        while (r < t.third) {
            r++;
            curans += (cnt[arr[r]] == 0);
            cnt[arr[r]]++;
        }
        while (l < t.sec) {
            cnt[arr[l]]--;
            curans -= (cnt[arr[l]] == 0);
            l++;
        }
        while (r > t.third) {
            cnt[arr[r]]--;
            curans -= (cnt[arr[r]] == 0);
            r--;
        }
        ans[t.first] = curans;
    }
    for (int i : ans) cout << i << "\n";
	return 0;
}
