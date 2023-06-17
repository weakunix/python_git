#include <iostream>
#include <vector>
#include <utility>
#include <set>
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

int n;
vector<int> ans;
vector<simps> rng;
set<int> st;
map<simps, int> idx;

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
        ans[idx[rng[i]]] = (st.upper_bound(rng[i].second) != st.begin());
        st.insert(rng[i].second);
    }
    for (int i : ans) cout << i << " ";
    cout << "\n";
    st.clear();
    for (int i = 0; i < n; i++) {
        ans[idx[rng[i]]] = (st.lower_bound(rng[i].second) != st.end());
        st.insert(rng[i].second);
    }
    for (int i : ans) cout << i << " ";
    cout << "\n";
	return 0;
}
