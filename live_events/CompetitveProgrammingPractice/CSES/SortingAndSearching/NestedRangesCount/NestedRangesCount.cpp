#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

template <class T> using index_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef long long ll;
typedef pair<int, int> simps;
typedef pair<int, simps> threesome;

#define sec second.first
#define third second.second
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define ook order_of_key
#define fbo find_by_order

int n;
vector<int> ans;
vector<simps> rng;
map<simps, int> idx;
index_set<simps> s;

bool cmp(simps a, simps b) {
    return (a.first == b.first) ? a.second > b.second : a.first < b.first;
}

int main() {
    cin >> n;
    ans.resize(n);
    rng.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> rng[i].first >> rng[i].second;
        idx[rng[i]] = i;
    }
    sort(all(rng), cmp);
    for (int i = n - 1; i >= 0; i--) {
        simps cur = {rng[i].second, n - i};
        ans[idx[rng[i]]] = s.ook(cur);
        s.insert(cur);
    }
    for (int i : ans) cout << i << " ";
    cout << "\n";
    s.clear();
    for (int i = 0; i < n; i++) {
        simps cur = {rng[i].second, n - i};
        ans[idx[rng[i]]] = i - s.ook(cur);
        s.insert(cur);
    }
    for (int i : ans) cout << i << " ";
    cout << "\n";
	return 0;
}
