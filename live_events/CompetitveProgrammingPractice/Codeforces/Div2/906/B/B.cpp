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

bool isgood(string& s) {
    char cur = s[0] == '0' ? '1' : '0';
    for (char c : s) {
        if (c == cur) return false;
        cur = c;
    }
    return true;
}

void subcase() {
    int n, m;
    string s, t;
    cin >> n >> m >> s >> t;

    if (isgood(s)) {
        cout << "YES\n";
        return;
    }
    if (not isgood(t) or t.size() % 2 == 0) {
        cout << "NO\n";
        return;
    }

    bool cons0 = false, cons1 = false;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != s[i - 1]) continue;
        if (s[i] == '0') cons0 = true;
        else cons1 = true;
    }

    if (cons0 and cons1) {
        cout << "NO\n";
        return;
    }
    if (cons0) {
        if (t[0] == '1') cout << "YES\n";
        else cout << "NO\n";
        return;
    }

    assert(cons1);

    if (t[0] == '0') cout << "YES\n";
    else cout << "NO\n";
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
