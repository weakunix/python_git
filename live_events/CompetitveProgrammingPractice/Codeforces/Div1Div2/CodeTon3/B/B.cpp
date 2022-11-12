#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

using namespace std;

typedef long long ll;
typedef pair<int, int> simps;

#define all(v) v.begin(), v.end()

void subcase() {
    int n;
    ll count = 0, x = 0, y = 0, ans = 0;
    char cur = '0';
    string s;
    cin >> n >> s;
    for (char c : s) {
        if (c == '0') x++;
        else y++;
        if (c == cur) count++;
        else {
            ans = max(count * count, ans);
            count = 1;
            cur = c;
        }
    }
    cout << max({x * y, count * count, ans}) << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
