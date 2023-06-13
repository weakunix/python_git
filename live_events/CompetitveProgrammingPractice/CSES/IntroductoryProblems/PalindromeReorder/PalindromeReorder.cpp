#include <iostream>
#include <string>
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

char extra = '.';
string s, half, ans;
vector<int> cnt(26);

int main() {
    cin >> s;
    for (char c : s) cnt[c - 'A']++;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2 != 0) {
            if (extra != '.') {
                cout << "NO SOLUTION\n";
                return 0;
            }
            extra = 'A' + i;
            cnt[i]--;
        }
        for (int j = 0; j < cnt[i] / 2; j++) half += 'A' + i;
    }
    ans = half;
    if (extra != '.') ans += extra;
    reverse(all(half));
    ans += half;
    cout << ans << "\n";
	return 0;
}
