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
    int cnt = 1;
    string s, a, b;
    cin >> s;
    while (cnt < s.size() and s[cnt] == '0') cnt++;

    if (cnt == s.size()) {
        cout << "-1\n";
        return;
    }

    a = s.substr(0, cnt);
    b = s.substr(cnt, s.size() - cnt);
    if (stoi(a) >= stoi(b)) {
        cout << "-1\n";
        return;
    }
    cout << a << " " << b << "\n";

	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> t;
	for (int i = 0; i < t; i++) subcase();
	return 0;
}
