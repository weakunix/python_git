#include <iostream>
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

int n, k, ans = 0;
vector<simps> movies;
multiset<int> times;

bool cmp(simps a, simps b) {
    return a.second < b.second;
}

int main() {
    cin >> n >> k;
    movies.resize(n);
    for (simps& s : movies) cin >> s.first >> s.second;
    sort(all(movies), cmp);
    for (int i = 0; i < k; i++) times.insert(0);
    for (simps& s : movies) {
        auto it = times.upper_bound(s.first);
        if (it == times.begin()) continue;
        ans++;
        it--;
        times.erase(it);
        times.insert(s.second);
    }
    cout << ans << "\n";
	return 0;
}
