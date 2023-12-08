#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <utility>
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

int t;

void subcase() {
    int n;
    map<int, int> cnt;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cur;
        cin >> cur;
        cnt[cur]++;
    }
    if (cnt.size() > 2) cout << "No\n";
    else if (cnt.size() == 1) cout << "Yes\n";
    else {
        auto it = cnt.begin();
        int res = it->second;
        it++;
        res -= it->second;
        cout << (abs(res) <= 1 ? "Yes\n" : "No\n");
    }
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
