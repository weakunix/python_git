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

void Subcase() {
    int n, red = -1, ans = 0;
    char c;
    string s;
    cin >> n >> c >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == c) {
            if (red == -1) red = i;
        }
        if (red == -1) continue;
        if (s[i] == 'g') {
            ans = max(i - red, ans);
            red = -1;
        }
    }
    if (red != -1) {
        for (int i = 0; i < n; i++) {
            if (s[i] == 'g') {
                ans = max(i + n - red, ans);
                break;
            }
        }
    }
    cout << ans << "\n";
	return;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) Subcase();
	return 0;
}
