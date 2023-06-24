#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <unordered_map>
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
vector<ll> dp;
vector<threesome> projects;
set<int> times;
unordered_map<int, int> compressmap;
unordered_map<int, vector<simps>> compressedprojects;

void compress() {
    for (threesome& t : projects) {
        times.insert(t.first);
        times.insert(t.sec);
    }
    for (int i : times) compressmap[i] = compressmap.size() + 1;
    for (threesome& t : projects) compressedprojects[compressmap[t.sec]].push_back({compressmap[t.first] - 1, t.third});
    return;
}

int main() {
    cin >> n;
    projects.resize(n);
    for (threesome& t : projects) cin >> t.first >> t.sec >> t.third;
    compress();
    dp.resize(compressmap.size() + 1);
    for (int i = 1; i <= compressmap.size(); i++) {
        dp[i] = dp[i - 1];
        for (simps& s : compressedprojects[i]) dp[i] = max(s.second + dp[s.first], dp[i]);
    }
    cout << dp.back() << "\n";
	return 0;
}
