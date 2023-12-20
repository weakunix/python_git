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

int t;

void subcase() {
    int cnt0 = 0, cnt1 = 0;
    string s;
    cin >> s;
    for (char c : s) {
        if (c == '0') cnt0++;
        else cnt1++;
    }
    for (char c : s) {
        if (c == '0') {
            if (cnt1 > 0) cnt1--;
            else break;
        }
        else {
            if (cnt0 > 0) cnt0--;
            else break;
        }
    }
    cout << cnt0 + cnt1 << "\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
