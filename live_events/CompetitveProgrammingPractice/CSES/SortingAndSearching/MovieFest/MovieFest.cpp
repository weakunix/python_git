#include <iostream>
#include <vector>
#include <utility>
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

int n, cur = 0, ans = 0;
vector<simps> movies;

bool cmp(simps a, simps b) {
    return a.second < b.second;
}

int main() {
    cin >> n;
    movies.resize(n);
    for (simps& s : movies) cin >> s.first >> s.second;
    sort(all(movies), cmp);
    for (simps& s : movies) {
        if (s.first < cur) continue;
        cur = s.second;
        ans++;
    }
    cout << ans << "\n";
	return 0;
}
