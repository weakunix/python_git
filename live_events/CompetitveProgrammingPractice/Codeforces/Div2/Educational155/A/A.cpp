#include <iostream>
#include <string>
#include <cstring>
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

const int N = 100;

int t;

void subcase() {
    int n, s[N], e[N];
    cin >> n;
    for (int i = 0; i < n; i++) cin >> s[i] >> e[i];
    for (int i = 1; i < n; i++) {
        if (s[i] >= s[0] and e[i] >= e[0]) {
            cout << -1 << "\n";
            return;
        }
    }
    cout << s[0] << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
