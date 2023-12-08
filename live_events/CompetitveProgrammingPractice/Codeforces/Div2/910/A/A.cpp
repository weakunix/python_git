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
    int n, k, cntb = 0;
    string s;
    cin >> n >> k >> s;
    for (char c : s) cntb += (c == 'B');
    if (cntb == k) {
        cout << "0\n";
        return;
    }
    cout << "1\n";
    if (cntb < k) {
        for (int i = 0; i < n; i++) {
            if (s[i] == 'A') cntb++;
            if (cntb == k) {
                cout << i + 1 << " B\n";
                return;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (s[i] == 'B') cntb--;
        if (cntb == k) {
            cout << i + 1 << " A\n";
            return;
        }
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
